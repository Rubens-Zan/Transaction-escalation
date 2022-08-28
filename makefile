MODULOS = transaction \
	viewEquivalentSchedules \
	auxiliar

OBJETOS = teste.o $(addsuffix .o,$(MODULOS))

.PHONY : all clean

teste : $(OBJETOS)

clean : 
	$(RM) $(OBJETOS)

purge : 
	$(RM) $(OBJETOS) teste
