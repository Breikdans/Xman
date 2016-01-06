#################################################################
# Exportador NoEscape 1.0
# Curso de Experto en Desarrollo de Videojuegos 
# Escuela Superior de Informatica - Univ. Castilla-La Mancha
# Carlos Gonzalez Morcillo - David Vallejo Fernandez
#################################################################

import bpy, os, sys
import mathutils
from math import *
from bpy import *

FOLDER = "/home/jose/dev/workspace/Xman/media/levels/level1/"
FILENAME = FOLDER + "output.xml"       # Archivo XML de salida
GRAPHNAME = "Graph"           # Nombre del objeto Mesh del grafo
EPSILON = 0.01                # Valor de distancia Epsilon

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
		if (
					 (empName.find("up") != -1)           #para poder comer
				or (empName.find("transport") != -1)	  #para irse al otro lado
				or (empName.find("normal") != -1)				#bolas normales	
				or (empName.find("start") != -1)				#punto inicio player
				or (empName.find("startEnemy") != -1)				#punto inicio fantasmas
				or (empName.find("forbidden") != -1)				#camino prohibido
				
				):
			if (isclose(empty, dv[key])):
				return 'type ="'+ empName[:-1] +'"'
	return 'type=""'

ID1 = ' '*2    # Identadores para el xml
ID2 = ' '*4    # Solo con proposito de obtener un xml "bonito"
ID3 = ' '*6
ID4 = ' '*8

graph = bpy.data.objects[GRAPHNAME]

dv = {}        # Diccionario de vertices                    
for vertex in graph.data.vertices:        
	dv[vertex.index+1] = vertex.co

de = {}        # Diccionario de aristas
for edge in graph.data.edges:           # Diccionario de aristas
	de[edge.index+1] = (edge.vertices[0], edge.vertices[1])

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
	print (ID2 + '<x>%f</x> <y>%f</y> <z>%f</z>' % (x,y,z))
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
	print ('<camera index="%i" fps="%i">' % (camIndex, bpy.data.scenes['Scene'].render.fps))
	print (ID1 + '<path>')
	for i in range (camFrames):
		cFrame = bpy.data.scenes['Scene'].frame_current
		bpy.data.scenes['Scene'].frame_set(cFrame+1)
		x,y,z = camera.matrix_world.translation
		qx,qy,qz,qw = camera.matrix_world.to_quaternion()
		print (ID2 + '<frame index="%i">' % (i+1))
		print (ID3 + '<position>')
		print (ID4 + '<x>%f</x> <y>%f</y> <z>%f</z>' % (x,y,z))
		print (ID3 + '</position>')
		print (ID3 + '<rotation>')
		print (ID4 + '<x>%f</x> <y>%f</y> <z>%f</z> <w>%f</w>' % (qx,qy,qz,qw))
		print (ID3 + '</rotation>')
		print (ID2 + '</frame>')
	print (ID1 + '</path>')
	print ('</camera>')

print ("</data>")

file.close()
sys.stdout = std