# Ocean Waves Generator Tool by Shem Skillman

[GitHub Repository Link](https://github.com/ShemSkillman/COMP3015-Optimized-Developer-Tool)

[Code Walkthrough Video Link]()

[]!(regular_wave.gif)

[]!(noise_wave.gif)

This is a tool that uses OpenGL and 2 shader techniques to generate ocean waves and an animated ship. 

## Environments used to test and write the code

IDE: Microsoft Visual Studio Community 2019 Version 16.11.3

OS : Microsoft Windows 10

## Features

 * Ocean waves are generated using a wave vertex animation shader for a regular pattern of waves or alternatively a noise shader that generates waves at random using perlin noise.
* Both shaders apply silhouette lines to all the indentifiable edges in the scene on top of a toon filter.
 * A ship which can be animated to 'react' to the waves by configuring its movement and position parameters. 
 * Ship movements include bobbing up and down and twisting left/right/up/down to mimic a boat floating on choppy waters.
 * Configurable light, ship, and wave settings on the console UI make the scene highly customizable.

## How to use

To start the tool open "Ocean Waves Generator Tool.exe" in the project folder.

Once the tool has been opened, use WASD or arrow key controls to move the orbital camera around to view the scene at different angles.

There is a console that can be opened by pressing the arrow button and then expanded by dragging the bottom right drag handle. 

Try playing around with the settings to create a calm or stormy ocean scene.

Light settings:

 * Light intensity - how bright should the light be?
 * Cartoon levels - defines the number of shades of colour each coloured object can have.
 * Light X, Y, Z position - where is the point light positioned in the scene?

 Wave settings:

 * Wave frequency - should more waves be generated smaller and closer together (high frequency) or should they be larger and further apart (low frequency)?
 * Wave move speed - how fast the waves are moving.
 * Wave height - how tall should the waves be?
 * Use noise - should the waves be generated randomly using perlin noise?
 * Wave color - colour of the ocean waves.
 * Wave line color - colour of the silhouette lines on the waves.
 * Wave line thickness - thickness of the silhouette lines on the waves.

 Ship settings:

  * Move speed - how fast should the ship move in reaction to the waves?
  * Starting Y rotation - the direction in which the ship is pointing.
  * Max X, Y, Z rotation - at what extent can the ship rotate in these axes during animation?
  * Invert X, Y, Z rotation - changes the timing of the rotation animations.
  * Ship Y position - how high the ship is positioned.
  * Bob height - how much should the ship be able to bob up and down?
  * Invert bob - changes the timing of the bob animation.
  * Ship color - the paint job of the ship.
  * Ship line color - color of the silhouette lines on the ship.
  * Ship line thickness - thickness of the silhouette lines on the ship.

## Background

What makes the tool special is the combination of wave generation with silhouette lines rendering. The silhouette lines shows the profile of waves in a stylized way to give the scene a cartoony look. On top of this, the user can change the ship movement/position, wave characteristics, and render properties to create potentially hundreds of different scenes.

I started with the provided project template and all external resources used are listed below.

## External Resources

SHIP.obj in the media folder was downloaded from [GrabCad](https://grabcad.com/library/low-poly-ship-1).

I am using the [imgui library](https://github.com/ocornut/imgui) v 1.86 to render UI.

Online Help:
 - [Implementing the orbital camera functionality](https://learnopengl.com/Getting-started/Camera)
 - [Using noise to generate waves](https://stackoverflow.com/questions/30397320/opengl-water-waves-with-noise)
 - [Importing imgui library](https://www.youtube.com/watch?v=S6ueaaN-Z2w)