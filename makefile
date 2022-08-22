MODULOS = transaction \
	viewEquivalentSchedules

OBJETOS = main.o $(addsuffix .o,$(MODULOS))

.PHONY : all clean

main : $(OBJETOS)

clean : 
	$(RM) $(OBJETOS)

purge : 
	$(RM) $(OBJETOS) main
