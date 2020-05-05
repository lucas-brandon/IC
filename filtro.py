import vtk
import sys

def ApplySmoothFilter(polydata, iterations, relaxation_factor):

    
    smoother = vtk.vtkSmoothPolyDataFilter()
    smoother.SetInputData(polydata)
    smoother.SetNumberOfIterations(iterations)
    smoother.SetRelaxationFactor(relaxation_factor)
    smoother.FeatureEdgeSmoothingOn()
    smoother.BoundarySmoothingOn()
    smoother.Update()
    normal = vtk.vtkPolyDataNormals()
    normal.SetInputData(smoother.GetOutput())
    normal.ComputePointNormalsOn()
    normal.ComputeCellNormalsOn()
    normal.Update()
    return normal.GetOutput()

reader = vtk.vtkOBJReader()
reader.SetFileName(sys.argv[1])
reader.Update()
poly_data = reader.GetOutput()

poly_data = ApplySmoothFilter(poly_data,15,0.1)
#print(type(poly_data))
# Create a mapper and actor for initial dataset
mapper = vtk.vtkPolyDataMapper()
mapper.SetInputData(poly_data)
actor = vtk.vtkActor()
actor.SetMapper(mapper)


# Visualise
renderer = vtk.vtkRenderer()
renderWindow = vtk.vtkRenderWindow()
renderWindow.AddRenderer(renderer)
renderWindowInteractor = vtk.vtkRenderWindowInteractor()
renderWindowInteractor.SetRenderWindow(renderWindow)

# Add actors and render
renderer.AddActor(actor)
renderer.SetBackground(0, 0, 0) # Background color white
renderWindow.SetSize(800, 800)
#renderWindow.Render()
#renderWindowInteractor.Start()

exporter = vtk.vtkOBJExporter()
exporter.SetRenderWindow( renderWindow )
exporter.SetFilePrefix( sys.argv[2] ) #create mtl and obj file.
exporter.Write()
