#!/bin/bash

# Directory where your invalid scene files are stored
SCENE_DIR="scenes/invalid"

# List of scene files to check
SCENE_FILES=(
    "Invalid_Ambient_Color_OutOfRange.rt"
    "Invalid_Ambient_OutOfRange.rt"
    "Invalid_Camera_FOV_OutOfRange.rt"
    "Invalid_Camera_Orientation_NotNormalized.rt"
    "Invalid_Common_Instructions.rt"
    "Invalid_Cylinder_.rt"
    "Invalid_Cylinder_Diameter_Negative.rt"
    "Invalid_Cylinder_Normal_NotNormalized.rt"
    "Invalid_Empty.rt"
    "Invalid_Identifier.rt"
    "Invalid_Kommas.rt"
    "Invalid_Light_.rt"
)

# Run valgrind for each scene file
for scene in "${SCENE_FILES[@]}"; do
    echo "Running Valgrind on $scene"
    valgrind --leak-check=full ./miniRT "$SCENE_DIR/$scene"
    echo "--------------------------------------------"
done