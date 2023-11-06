#---------------------------------------------------------
# macros
RM = /bin/rm -f  # for removing
CC = g++         # compiler
#---------------------------------------------------------

#---------------------------------------------------------
# vars
EXEC=main
#---------------------------------------------------------
CLASS=Asteriod
#---------------------------------------------------------
CLASS2=AnimatedObject
#---------------------------------------------------------
#CLASS2=Shape
CLASS3=BoundingBox
#---------------------------------------------------------
CLASS4=ComplexGraphicObject
# CLASS3=Face
#---------------------------------------------------------
#CLASS4=Ellipse
CLASS5=Ellipse
#---------------------------------------------------------
#CLASS5=Orangutan
CLASS6=Game
#---------------------------------------------------------
CLASS7=GraphicObject
#---------------------------------------------------------
CLASS8=Missile
#---------------------------------------------------------
CLASS9=Object
#---------------------------------------------------------
CLASS10=Polygon
#---------------------------------------------------------
CLASS11=Rectangle
#---------------------------------------------------------
CLASS12=Ship
#---------------------------------------------------------
CLASS13=World
#---------------------------------------------------------
#---------------------------------------------------------
CPPFLAGS=-I. -lglut -lGLU -lGL -lstdc++ -lm
#-std=c++11 -fmax-errors=1 -Wall -O3
#---------------------------------------------------------

#---------------------------------------------------------
all: ${EXEC} # execute "make"
#---------------------------------------------------------
${EXEC}:  ${EXEC}.o ${CLASS}.o ${CLASS2}.o ${CLASS3}.o ${CLASS4}.o ${CLASS5}.o ${CLASS6}.o ${CLASS7}.o ${CLASS8}.o ${CLASS9}.o ${CLASS10}.o ${CLASS11}.o ${CLASS12}.o ${CLASS13}.o
	${CC} ${EXEC}.o ${CLASS}.o ${CLASS2}.o ${CLASS3}.o ${CLASS4}.o ${CLASS5}.o ${CLASS6}.o ${CLASS7}.o ${CLASS8}.o ${CLASS9}.o ${CLASS10}.o ${CLASS11}.o ${CLASS12}.o ${CLASS13}.o -o ${EXEC} ${CPPFLAGS}
#---------------------------------------------------------
${EXEC}.o: ${EXEC}.cpp 
	${CC} -c ${EXEC}.cpp -o ${EXEC}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS}.o: ${CLASS}.cpp ${CLASS}.h
	${CC} -c ${CLASS}.cpp -o ${CLASS}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS2}.o: ${CLASS2}.cpp ${CLASS2}.h
	${CC} -c ${CLASS2}.cpp -o ${CLASS2}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS3}.o: ${CLASS3}.cpp ${CLASS3}.h
	${CC} -c ${CLASS3}.cpp -o ${CLASS3}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS4}.o: ${CLASS4}.cpp ${CLASS4}.h
	${CC} -c ${CLASS4}.cpp -o ${CLASS4}.o ${CPPFLAGS}
#---------------------------------------------------------9
${CLASS5}.o: ${CLASS5}.cpp ${CLASS5}.h
	${CC} -c ${CLASS5}.cpp -o ${CLASS5}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS6}.o: ${CLASS6}.cpp ${CLASS6}.h
	${CC} -c ${CLASS6}.cpp -o ${CLASS6}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS7}.o: ${CLASS7}.cpp ${CLASS7}.h
	${CC} -c ${CLASS7}.cpp -o ${CLASS7}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS8}.o: ${CLASS8}.cpp ${CLASS8}.h
	${CC} -c ${CLASS8}.cpp -o ${CLASS8}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS9}.o: ${CLASS9}.cpp ${CLASS9}.h
	${CC} -c ${CLASS9}.cpp -o ${CLASS9}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS10}.o: ${CLASS10}.cpp ${CLASS10}.h
	${CC} -c ${CLASS10}.cpp -o ${CLASS10}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS11}.o: ${CLASS11}.cpp ${CLASS11}.h
	${CC} -c ${CLASS11}.cpp -o ${CLASS11}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS12}.o: ${CLASS12}.cpp ${CLASS12}.h
	${CC} -c ${CLASS12}.cpp -o ${CLASS12}.o ${CPPFLAGS}
#---------------------------------------------------------
${CLASS13}.o: ${CLASS13}.cpp ${CLASS13}.h
	${CC} -c ${CLASS13}.cpp -o ${CLASS13}.o ${CPPFLAGS}
#---------------------------------------------------------
clean: # delete object files and executables
	$(RM) ${EXEC}.o ${EXEC} ${CLASS}.o ${CLASS} ${CLASS2}.o ${CLASS2} ${CLASS3}.o ${CLASS3} ${CLASS4}.o ${CLASS4} ${CLASS5}.o ${CLASS5} ${CLASS6}.o ${CLASS6} ${CLASS7}.o ${CLASS7} ${CLASS8}.o ${CLASS8} ${CLASS9}.o ${CLASS9} ${CLASS10}.o ${CLASS10} ${CLASS11}.o ${CLASS11} ${CLASS12}.o ${CLASS12} ${CLASS13}.o ${CLASS13}
#---------------------------------------------------------
#---------------------------------------------------------
