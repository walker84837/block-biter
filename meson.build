project('blockbiter', 'cpp')

# Compiler and Flags
cpp_args = [
  '-O2',
  '-std=gnu++17',
  '-Wall',
  '-Wextra',
  '-pedantic',
]

# Source Files
sources = files('src/main.cpp', 'src/game.cpp', 'src/err_handling.cpp')

# Create the Executable
exe = executable(
  'blockbiter', 
  sources,
  include_directories: include_directories('include'),
  link_args: ['-lraylib', '-flto=auto'],
  cpp_args: cpp_args,
  install: true,
  install_dir: 'bin'
)
