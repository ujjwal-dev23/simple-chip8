project('chip8', 'cpp', default_options : ['cpp_std=c++20', 'buildtype=release'])

sources = files(
  'src/chip8.cpp',
  'src/graphics.cpp',
  'src/input.cpp',
  'src/main.cpp',
  )

deps = [dependency('sdl3')]

executable('chip8', sources, dependencies: deps)
