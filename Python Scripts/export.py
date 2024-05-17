import importOBJ

num = ""

for i in range(1, 625):
    if i < 10:
        num = f"00{i}"
    elif i >= 10 and i < 100:
        num = f"0{i}"
    else:
        num = f"{i}"

    mesh_name = 'Mesh'+num

    Gui.Selection.clearSelection()
    Gui.Selection.addSelection('Actuator',mesh_name)

    __objs__ = []
    __objs__.append(FreeCAD.getDocument("Actuator").getObject(mesh_name))

    if hasattr(importOBJ, "exportOptions"):
        options = importOBJ.exportOptions(f"C:/Users/Marci/Desktop/Dokumentacja wszelaka/Studia/ROK III/SEM VI/PP/Meshes/Mesh{i}.obj")
        importOBJ.export(__objs__, f"C:/Users/Marci/Desktop/Dokumentacja wszelaka/Studia/ROK III/SEM VI/PP/Meshes/Mesh{i}.obj", options)
    else:
        importOBJ.export(__objs__, f"C:/Users/Marci/Desktop/Dokumentacja wszelaka/Studia/ROK III/SEM VI/PP/Meshes/Mesh{i}.obj")

    del __objs__
