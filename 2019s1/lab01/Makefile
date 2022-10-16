MAIN = lab01

SRC = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
HDR = $(wildcard *.h)
CC = gcc
GFLAGS = -std=c99 -Wall -Werror -Werror=vla -pedantic-errors -g -lm
SHELL = bash

$(MAIN): $(OBJ) $(HDR)
	$(CC) $(GFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(GFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN) *.o

.PHONY: testar_tudo
testar_tudo: $(MAIN)
	@if [ ! -d testes_abertos ] ; then \
		echo "*****************************************************************" ; \
		echo "Copie o diretório 'testes_abertos' para a mesma pasta do Makefile" ; \
		echo "*****************************************************************" ; \
		exit 1 ; \
	fi ; \
	for entrada in testes_*/*.in ; do \
		saida=$$(echo "$$entrada" | sed -re 's/\.in$$/.out/' ) ; \
		resposta=$$(echo "$$entrada" | sed -re 's/\.in$$/.res/' ) ; \
		./$(MAIN) < "$$entrada" > "$$saida" ; \
		echo ; \
		echo -n "Testando $$entrada: " ; \
		if diff "$$saida" "$$resposta" > /dev/null ;  then \
			echo "OK" ; \
		else \
			echo "FALHOU" ; \
		fi ; \
	done

.PHONY: tempo
tempo: $(MAIN)
	@if [ ! -d testes_abertos ] ; then \
		echo "*****************************************************************" ; \
		echo "Copie o diretório 'testes_abertos' para a mesma pasta do Makefile" ; \
		echo "*****************************************************************" ; \
		exit 1 ; \
	fi ; \
	for entrada in testes_*/*.in ; do \
		saida=$$(echo "$$entrada" | sed -re 's/\.in$$/.out/' ) ; \
		echo -n "Tempo para $$entrada: " ; \
		time ( ./$(MAIN) < "$$entrada" > "$$saida" ) ; \
		echo ; \
	done



.PHONY: baixar_fechados
FECHADOS = 16 17 18 19 20 21 22 23 24 25
ULTIMO_FECHADO = 25
baixar_fechados:
	@mkdir -p testes_fechados ; \
	if [ -f testes_fechados/arq$(ULTIMO_FECHADO).res ] ; then \
		echo "Testes fechados já foram baixados." ; \
		exit 0 ; \
	fi ; \
	lab=$$(echo "$(MAIN)" | sed -re 's/lab//') ; \
	curl -sk "https://susy.ic.unicamp.br:9999/mc202def/DRAFT-$$lab/dados/arq$(ULTIMO_FECHADO).in" | grep -e '<HTML>' ; \
	if [ $$?  = "0" ] ; then \
		echo "*********************************************************" ; \
		echo "Certifique-se de que os testes fechados estejam liberados" ; \
		echo "*********************************************************" ; \
		exit 1 ; \
	fi ; \
	for i in $(FECHADOS) ; do \
		for ext in .in .res ; do \
			curl -k "https://susy.ic.unicamp.br:9999/mc202def/DRAFT-$$lab/dados/arq$$i$$ext" > testes_fechados/arq$$i$$ext ; \
		done ; \
	done
