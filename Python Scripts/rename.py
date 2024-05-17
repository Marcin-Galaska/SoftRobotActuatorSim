import os

def rename_files(directory):
    pressure_values = range(0, 2401, 100)
    force_values = range(0, 25)

    count = 1
    # Iterate over pressure and force values
    for force in force_values:
        for pressure in pressure_values:
            # Construct the new file name
            new_filename = f"{pressure}_{force}.obj"
            # Construct the current file path
            old_filename = f"Mesh{count}.obj"
            old_filepath = os.path.join(directory, old_filename)
            new_filepath = os.path.join(directory, new_filename)
            try:
                # Rename the file
                os.rename(old_filepath, new_filepath)
                print(f"Renamed: {old_filename} -> {new_filename}")
            except FileNotFoundError:
                print(f"File not found: {old_filename}")
            count += 1

# Replace 'directory_path' with the path of the directory containing the files
directory_path = 'C:/Users/Marci/Desktop/Dokumentacja wszelaka/Studia/ROK III/SEM VI/PP/Meshes'
rename_files(directory_path)
