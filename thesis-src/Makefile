###############################################################################
##									     ##
##	File:     Makefile						     ##
##	Author:   Alison Chaiken					     ##
##	Created:  Mon Nov  7 23:18:48 EST 1988				     ##
##	Contents: makefile for makeing a thesis (any...)		    ##
##									     ##
##	Copyright (c) 1988 Alison Chaiken.				     ##
##	All rights reserved.						     ##
##									     ##
##	$Log$								     ##
###############################################################################

.SUFFIXES:
.SUFFIXES: .aux .tex

test: abstract.aux titlepage.aux acknowledge.aux acro.aux


.tex.aux:
	latex qthesis.tex $*.tex
