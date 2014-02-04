CXX = g++ 
CXXFLAGS = -g -lX11
EXEC = chess 
OBJECTS = grid.o tile.o player.o piece.o pawn.o queen.o bishop.o rook.o knight.o king.o display.o observer.o subject.o window-v2.o
GRAPHICO = display.o observer.o subject.o window-v2.o

${EXEC}: main.o ${OBJECTS}
	${CXX} main.o ${OBJECTS} ${CXXFLAGS} -o ${EXEC}

graphics: testGraphicsMain.o ${GRAPHICO} ${OBJECTS}
	${CXX} testGraphicsMain.o ${OBJECTS} ${GRAPHICO} -o graphics -lX11

.PHONY: clean

clean:
	rm ${OBJECTS} ${GRAPHICO} ${EXEC} 

