use bevy::{color::Color, input::ButtonInput, prelude::*};
use rand::prelude::*;
use serde::Deserialize;
use std::fs;

const GRID_WIDTH: usize = 32;
const GRID_HEIGHT: usize = 32;
const SNAKE_SPEED: f32 = 0.5;
const GREEN: Color = Color::linear_rgb(0.0, 1.0, 0.0);
const RED: Color = Color::linear_rgb(1.0, 0.0, 0.0);

// Enum for directions
#[derive(PartialEq, Copy, Clone)]
enum MoveDirection {
    Up,
    Down,
    Left,
    Right,
}

// Struct for configuration file
#[derive(Deserialize)]
struct ConfigData {
    target_fps: u32,
    width: u32,
    height: u32,
}

#[derive(Default, Component)]
struct SnakeHead;
#[derive(Default, Component)]
struct Food;

//#[derive(Component)]
//struct Block {
//    x: usize,
//    y: usize,
//}

//#[derive(Resource)]
//struct GameConfig {
//    frame_rate: u64,
//    screen_width: u32,
//    screen_height: u32,
//}

#[derive(Resource)]
struct SnakeState {
    direction: MoveDirection,
    body: Vec<Entity>,
    alive: bool,
    score: u32,
}

impl Default for SnakeState {
    fn default() -> Self {
        SnakeState {
            direction: MoveDirection::Right,
            body: Vec::new(),
            alive: true,
            score: 0,
        }
    }
}

// Game initialization system
fn setup(mut commands: Commands) {
    commands.spawn(Camera2dBundle::default());

    // Load initial snake position and food
    let head = commands
        .spawn(SpriteBundle {
            transform: Transform::from_xyz(0.0, 0.0, 0.0),
            sprite: Sprite {
                color: GREEN, // set color to GREEN constant
                ..default()
            },
            ..default()
        })
        .insert(SnakeHead)
        .id();
    commands.insert_resource(SnakeState {
        body: vec![head],
        direction: MoveDirection::Up,
        alive: true,
        score: 0,
    });

    // Spawn initial food
    spawn_food(commands);
}

// Input handling system
fn input_system(keyboard_input: Res<ButtonInput<KeyCode>>, mut snake_state: ResMut<SnakeState>) {
    if keyboard_input.just_pressed(KeyCode::ArrowUp) && snake_state.direction != MoveDirection::Down
    {
        snake_state.direction = MoveDirection::Up;
    }
    if keyboard_input.just_pressed(KeyCode::ArrowDown) && snake_state.direction != MoveDirection::Up
    {
        snake_state.direction = MoveDirection::Down;
    }
    if keyboard_input.just_pressed(KeyCode::ArrowLeft)
        && snake_state.direction != MoveDirection::Right
    {
        snake_state.direction = MoveDirection::Left;
    }
    if keyboard_input.just_pressed(KeyCode::ArrowRight)
        && snake_state.direction != MoveDirection::Left
    {
        snake_state.direction = MoveDirection::Right;
    }
}

// System to move the snake
fn move_snake(
    mut commands: Commands,
    mut snake_state: ResMut<SnakeState>,
    time: Res<Time>,
    mut query: Query<(Entity, &mut Transform, Option<&SnakeHead>)>,
) {
    let delta_time = time.delta_seconds();
    if delta_time < SNAKE_SPEED {
        return;
    }

    let mut head_pos = None;

    // Move each body segment
    for (entity, transform, is_head) in query.iter_mut() {
        let position = (transform.translation.x, transform.translation.y);
        if is_head.is_some() {
            head_pos = Some((entity, position));
            break;
        }
    }

    if let Some((head, (x, y))) = head_pos {
        let (new_x, new_y) = match snake_state.direction {
            MoveDirection::Up => (x, y + 1.0),
            MoveDirection::Down => (x, y - 1.0),
            MoveDirection::Left => (x - 1.0, y),
            MoveDirection::Right => (x + 1.0, y),
        };

        // Wrap-around for grid boundaries
        let wrapped_x = (new_x + GRID_WIDTH as f32) % GRID_WIDTH as f32;
        let wrapped_y = (new_y + GRID_HEIGHT as f32) % GRID_HEIGHT as f32;

        // Spawn new segment at the wrapped position
        commands
            .entity(head)
            .insert(Transform::from_xyz(wrapped_x, wrapped_y, 0.0));

        // Check for food collision
        if let Some((food_entity, _, _)) =
            query.iter_mut().find(|(_, _, is_food)| is_food.is_some())
        {
            // Add a new segment to the snake's body
            let new_body_segment = commands
                .spawn(SpriteBundle {
                    transform: Transform::from_xyz(wrapped_x, wrapped_y, 0.0),
                    sprite: Sprite {
                        color: GREEN,
                        ..default()
                    },
                    ..default()
                })
                .id();
            snake_state.body.push(new_body_segment);

            // Respawn food
            commands.entity(food_entity).despawn();
            spawn_food(commands);
        }
    }
}

// Function to spawn food at a random position
fn spawn_food(mut commands: Commands) {
    let x = rand::thread_rng().gen_range(0..GRID_WIDTH);
    let y = rand::thread_rng().gen_range(0..GRID_HEIGHT);
    commands
        .spawn(SpriteBundle {
            transform: Transform::from_xyz(x as f32, y as f32, 0.0),
            sprite: Sprite {
                color: RED,
                ..default()
            },
            ..default()
        })
        .insert(Food);
}

// System to check game over condition
fn game_over(mut snake_state: ResMut<SnakeState>) {
    if !snake_state.alive {
        println!("Game Over! Score: {}", snake_state.score);
        snake_state.body.clear();
        snake_state.alive = true;
        snake_state.score = 0;
        // Additional reset logic if needed
    }
}

fn main() {
    // Load configuration from JSON
    // let config: GameConfig = load_config();

    App::new()
        .add_plugins(DefaultPlugins)
        // insert_resource(config)
        .add_systems(Startup, setup)
        .add_systems(Update, (input_system, move_snake, game_over))
        .run();
}

// Function to load configuration
//fn load_config() -> GameConfig {
//    let data = fs::read_to_string("config.json").expect("Could not read config.json");
//    let config: ConfigData = serde_json::from_str(&data).expect("Invalid config format");
//    GameConfig {
//        frame_rate: (config.target_fps as f64 * 0.75) as u64,
//        screen_width: config.width,
//        screen_height: config.height,
//    }
//}
