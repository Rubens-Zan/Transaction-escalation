MODULOS = transaction \
	viewEquivalentSchedules \
	auxiliar

OBJETOS = escalona.o $(addsuffix .o,$(MODULOS))

.PHONY : all clean

escalona : $(OBJETOS)

clean : 
	$(RM) $(OBJETOS)

purge : 
	$(RM) $(OBJETOS) escalona
