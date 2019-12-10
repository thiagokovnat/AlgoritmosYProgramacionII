from Graph import *


if __name__ == '__main__':

    g = Grafo()

    g.agregarVertice('a')
    g.agregarVertice('b')
    g.agregarVertice('c')
    g.agregarVertice('d')
    g.agregarVertice('e')
    g.agregarVertice('f')

    g.agregarArista('a', 'b', 7)  
    g.agregarArista('a', 'c', 9)
    g.agregarArista('a', 'f', 14)
    g.agregarArista('b', 'c', 10)
    g.agregarArista('b', 'd', 15)
    g.agregarArista('c', 'd', 11)
    g.agregarArista('c', 'f', 2)
    g.agregarArista('d', 'e', 6)
    g.agregarArista('e', 'f', 9)
    g.caminoMinimo('a')
"""
    for v in g:
        print(v)
        for w in v.getAdyacentes():
            vid = v.getClave()
            wid = w.getClave()
            print ('( %s , %s, %3d)'  % ( vid, wid, v.getPeso(w)))
"""

 #  g.DFS('a')
 #  g.BFS('a')

   
"""  
    g2 = Grafo()
    g2.agregarVertice('a')
    g2.agregarVertice('b')					
    g2.agregarVertice('c')							
    g2.agregarVertice('d')
    g2.agregarVertice('f')
    g2.agregarVertice('e')

    g2.agregarArista('a', 'b', 0)
    g2.agregarArista('b', 'c', 0)
    g2.agregarArista('c', 'f', 0)
    g2.agregarArista('b', 'd', 0)
    g2.agregarArista('d', 'e', 0)
    g2.agregarArista('e', 'a', 0)
   # g2.DFS('a')

    #g2.BFS('a')
"""
