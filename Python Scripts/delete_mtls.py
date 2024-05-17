import os

def delete_mtl_files(directory):
    # Traverse through the directory
    for root, dirs, files in os.walk(directory):
        for file in files:
            # Check if file has .mtl extension
            if file.endswith(".mtl"):
                try:
                    # Construct the file path
                    file_path = os.path.join(root, file)
                    # Delete the file
                    os.remove(file_path)
                    print(f"Deleted: {file_path}")
                except OSError as e:
                    print(f"Error deleting {file_path}: {e}")

# Replace 'directory_path' with the path of the directory containing the .mtl files
directory_path = 'C:/Users/Marci/Desktop/Dokumentacja wszelaka/Studia/ROK III/SEM VI/PP/Meshes'
delete_mtl_files(directory_path)