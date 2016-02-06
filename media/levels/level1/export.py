#################################################################
# Exportador xman
#################################################################

import bpy, os, sys
import mathutils
from math import *
from bpy import *

FOLDER = "/home/jose/dev/workspace/Xman/media/levels/level1/"
FILENAME = FOLDER + "output.xml"       # Archivo XML de salida
GRAPHNAME = "Graph"           # Nombre del objeto Mesh del grafo
EPSILON = 0.03                # Valor de distancia Epsilon

# ----- isclose -------------------------------------------------
# Decide si un empty coincide con un vertice del grafo
# ---------------------------------------------------------------
def isclose(empty, coord):
	xo, yo, zo = coord
	xd, yd, zd = empty.location
	v = mathutils.Vector((xo-xd, yo-yd, zo-zd))
	if (v.length < EPSILON):
		return True
	else:
		return False

# ----- gettype -------------------------------------------------
# Devuelve una cadena con el tipo del nodo del grafo
# ---------------------------------------------------------------
def gettype (dv, key):

	
	obs = [ob for ob in bpy.data.objects if ob.type == 'EMPTY']
	for empty in obs:
		empName = empty.name
		
		myType="";
		myBall = "";
	
		if (empName.find("transportLeft") != -1):
				myType = "transportLeft"
		if (empName.find("transportRight") != -1):
				myType = "transportRight"				
		elif(empName.find("stPlayer") != -1):
				myType = "stPlayer"			
		elif(empName.find("stEnemy") != -1):
				myType = "stEnemy"						
		elif(empName.find("forbidden") != -1):
				myType = "forbidden"
	
		if (empName.find("ballPower") != -1):
				myBall = "ballPower"
		elif(empName.find("ballNone") != -1):
				myBall = "ballNone"
				
		if (isclose(empty, dv[key])):
				return 'type ="'+ myType +'" ball ="'+ myBall +'"'
	return 'type="" ball=""'

ID1 = ' '*2    # Identadores para el xml
ID2 = ' '*4    # Solo con proposito de obtener un xml "bonito"
ID3 = ' '*6
ID4 = ' '*8

graph = bpy.data.objects[GRAPHNAME]

dv = {}        # Diccionario de vertices                    
for vertex in graph.data.vertices:        
	dv[vertex.index] = vertex.co

de = {}        # Diccionario de aristas
for edge in graph.data.edges:           # Diccionario de aristas
	de[edge.index] = (edge.vertices[0], edge.vertices[1])
	
file = open(FILENAME, "w")
std=sys.stdout
sys.stdout=file

print ("<?xml version='1.0' encoding='UTF-8'?>\n")
print ("<data>\n")


# ------------- Exportacion del grafo -------------------------------
print ("<graph>")
for key in dv.keys():
	print (ID1 + '<vertex index="' + str(key) + '" '+ gettype(dv,key) +'>')
	x,y,z = dv[key]
	print (ID2 + '<x>%.4f</x> <y>%.4f</y> <z>%.4f</z>' % (x,y,z))
	print (ID1 + '</vertex>')
for key in de.keys():
	print (ID1 + '<edge>')
	v1,v2 = de[key]
	print (ID2 + '<vertex>%i</vertex> <vertex>%i</vertex>' % (v1,v2))
	print (ID1 + '</edge>')
print ("</graph>\n")

# ------------- Exportacion de la camara -----------------------------
obs = [ob for ob in bpy.data.objects if ob.type == 'CAMERA']
for camera in obs:
	camId = camera.name
	camName = camId.split("_")[0]
	camIndex = int(camId.split("_")[1])
	camFrames = int (camId.split("_")[2])
	print ('<camera index="%i" fps="%i" name="%s">' % (camIndex, bpy.data.scenes['Scene'].render.fps, camName))
	#print (ID1 + '<path>')
	for i in range (camFrames):
		cFrame = bpy.data.scenes['Scene'].frame_current
		bpy.data.scenes['Scene'].frame_set(i)
		x,y,z = camera.matrix_world.translation
		qx,qy,qz,qw = camera.matrix_world.to_quaternion()
		print (ID1 + '<frame index="%i">' % (i))
		print (ID2 + '<position>')
		print (ID3 + '<x>%f</x> <y>%f</y> <z>%f</z>' % (x,y,z))
		print (ID2 + '</position>')
		print (ID2 + '<rotation>')
		print (ID3 + '<x>%f</x> <y>%f</y> <z>%f</z> <w>%f</w>' % (qx,qy,qz,qw))
		print (ID2 + '</rotation>')
		print (ID1 + '</frame>')
	#print (ID1 + '</path>')
	print ('</camera>')


print ("</data>")

file.close()
sys.stdout = std