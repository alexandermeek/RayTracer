# RayTracer
Ray tracing application for a third year project.

Options for configuring the scene can be found in the options.txt file.

## Different scenes:
| model name     | scale | filename       |
| -------------- | ----- | -------------- |
| original scene | 0.35  | original_scene |
| diamond        | 1.5   | diamond        |
| dodecahedron   | 0.5   | dodecahedron   |
| bunny          | 6     | bun_zipper     |
| dragon         | 2     | dragon_vrip    |
***Note:*** Various models have additional, lower resolution models available. The filename adds a suffix of _res2, 3 or 4.

Any additional downloaded models can be placed in the models directory and used likewise.

## Compilation:
To compile using gcc: `g++ --std=c++11 *.cpp -o raytracer` (if within the internal RayTracer directory)