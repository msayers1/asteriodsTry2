#---------------------------------------------------------
# macros
RM = /bin/rm -f  # for removing
CC = g++         # compiler
#---------------------------------------------------------

#---------------------------------------------------------
# vars
EXEC=main
#---------------------------------------------------------
CLASS=AnimatedObject
#---------------------------------------------------------
#CLASS2=Shape
CLASS2=Ellipse
#---------------------------------------------------------
CLASS3=ComplexGraphicObject
# CLASS3=Face
#---------------------------------------------------------
#CLASS4=Ellipse
CLASS4=Game
#---------------------------------------------------------
#CLASS5=Orangutan
CLASS5=Polygon
#---------------------------------------------------------
CLASS6=GraphicObject
#---------------------------------------------------------
CLASS7=Rectangle
#---------------------------------------------------------
CLASS8=Ship
#---------------------------------------------------------
CLASS9=World
#---------------------------------------------------------
CLASS10=Missile
#---------------------------------------------------------
CLASS11=Object
#---------------------------------------------------------
CLASS12=BoundingBox
#---------------------------------------------------------
#---------------------------------------------------------
CPPFLAGS=-I. -lglut -lGLU -lGL -lstdc++ -lm
#-std=c++11 -fmax-errors=1 -Wall -O3
#---------------------------------------------------------

#---------------------------------------------------------
all: ${EXEC} # execute "make"
#---------------------------------------------------------
${EXEC}: ${EXEC}.o ${CLASS}.o ${CLASS2}.o ${CLASS3}.o ${CLASS4}.o  ${CLASS5}.o ${CLASS6}.o ${CLASS7}.o ${CLASS8}.o ${CLASS9}.o ${CLASS10}.o ${CLASS11}.o ${CLASS12}.o ${CLASS13}.o
	${CC} ${EXEC}.o ${CLASS}.o ${CLASS2}.o ${CLASS3}.o ${CLASS4}.o ${CLASS5}.o ${CLASS6}.o ${CLASS7}.o ${CLASS8}.o ${CLASS9}.o ${CLASS10}.o  ${CLASS11}.o ${CLASS12}.o ${CLASS13}.o -o ${EXEC} ${CPPFLAGS}
#---------------------------------------------------------
${EXEC}.o: ${EXEC}.cpp 
	${CC} -c ${EXEC}.cpp -o ${EXEC}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS}.o: ${CLASS}.cpp 
	${CC} -c ${CLASS}.cpp -o ${CLASS}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS2}.o: ${CLASS2}.cpp 
	${CC} -c ${CLASS2}.cpp -o ${CLASS2}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS3}.o: ${CLASS3}.cpp 
	${CC} -c ${CLASS3}.cpp -o ${CLASS3}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS4}.o: ${CLASS4}.cpp 
	${CC} -c ${CLASS4}.cpp -o ${CLASS4}.o ${CPPFLAGS}
#---------------------------------------------------------9
${CLASS5}.o: ${CLASS5}.cpp 
	${CC} -c ${CLASS5}.cpp -o ${CLASS5}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS6}.o: ${CLASS6}.cpp 
	${CC} -c ${CLASS6}.cpp -o ${CLASS6}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS7}.o: ${CLASS7}.cpp 
	${CC} -c ${CLASS7}.cpp -o ${CLASS7}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS8}.o: ${CLASS8}.cpp 
	${CC} -c ${CLASS8}.cpp -o ${CLASS8}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS9}.o: ${CLASS9}.cpp 
	${CC} -c ${CLASS9}.cpp -o ${CLASS9}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS10}.o: ${CLASS10}.cpp 
	${CC} -c ${CLASS10}.cpp -o ${CLASS10}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS11}.o: ${CLASS11}.cpp 
	${CC} -c ${CLASS11}.cpp -o ${CLASS11}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS12}.o: ${CLASS12}.cpp 
	${CC} -c ${CLASS12}.cpp -o ${CLASS12}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS13}.o: ${CLASS13}.cpp 
	${CC} -c ${CLASS13}.cpp -o ${CLASS13}.o ${CPPFLAGS}
#---------------------------------------------------------
clean: # delete object files and executables
	$(RM) ${EXEC}.o ${EXEC} ${CLASS}.o ${CLASS} ${CLASS2}.o ${CLASS2} ${CLASS3}.o ${CLASS3} ${CLASS4}.o ${CLASS4} ${CLASS5}.o ${CLASS5} ${CLASS6}.o ${CLASS6} ${CLASS7}.o ${CLASS7} ${CLASS8}.o ${CLASS8} ${CLASS9}.o ${CLASS9} ${CLASS10}.o ${CLASS10} ${CLASS10}.o ${CLASS11} ${CLASS11}.o ${CLASS12} ${CLASS12}.o ${CLASS13} ${CLASS13}.o 
#---------------------------------------------------------
