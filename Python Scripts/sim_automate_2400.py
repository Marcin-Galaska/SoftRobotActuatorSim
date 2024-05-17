from os.path import join
import FreeCAD as App
import Mesh
from femmesh import femmesh2mesh
from femtools import ccxtools

pressure = 2400
force = 0.0000001
scale = 1
fea = ccxtools.FemToolsCcx()
path = join(App.getResourceDir(), "examples", "Actuator.FCStd")

for i in range(25):
	fea.purge_results()
	fea.run()

	doc = App.openDocument(path)
	fem_mesh = doc.FEMMeshGmsh.FemMesh
	result = doc.CCX_Results
	doc.ConstraintPressure.Pressure = pressure / 1000000
	out_mesh = femmesh2mesh.femmesh_2_mesh(fem_mesh, result, scale)
	mesh_obj = Mesh.Mesh(out_mesh)
	Mesh.show(mesh_obj)

	force = force + 1
	doc.ConstraintForce.Force = force
