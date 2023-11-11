# Build example 

- Configure example project with cmake like you do in other project.

- Configure cmake build

```bash
cmake -S . -B build 
```

- Run build

```bash
cd build; make 
```

- Run example project

```bash
cd build; ./example RickaPrincy
```

- After those command, you should have a file `main.ts` inside the `build` (the example build folder) which is an example of template generated

- Change `RickaPrincy` to change the main.ts content