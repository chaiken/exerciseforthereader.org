###############################################################################
##									     ##
##	File:     Makefile						     ##
##	Author:   Wolfgang S. Rupprecht <wolfgang@charlotte.dontspam.wsrcc.com>		     ##
##	Created:  Thu Oct 18 19:39:05 EDT 1990				     ##
##	Contents: makefile for letter directory  ##
##									     ##
##	Copyright (c) 1990 Wolfgang S. Rupprecht.			     ##
##	All rights reserved.						     ##
##									     ##
##	$Header$							     ##
###############################################################################

.SUFFIXES:
.SUFFIXES: .ps .dvi .tex

checklinks:
	weblint -e bad-link recipes/*.html

clean:
	/bin/rm -f *.dvi *.log *.jep *.dvi-jep *.aux *~ *.err *.dlog 

newstuff:
	weblint misspeak/levin/*.html

nio:
	weblint niojoint niorapid niomrs

weblint:
	weblint coolstuff.html bigcs.html books recipes 

allweblint:
	weblint *.html ani bnjvst bnapl bnmrs bscco fecrfemmm fecucoapl fecucommm fesiMMM fesiprb fesixrf intermagnio jmmm  mrtempdep newnio rapid rsi uxopaper misspeak niojoint

.tex.dvi:
	TEXINPUTS=.:/u/local/lib/texmf/tex/latex/base:/u/local/lib/texmf/tex/latex/physics:/u/alison/txt/semsty/:/u/local/lib/texmf/tex/dvips/: latex $*

.dvi.ps:
	dvips $*.dvi

.tex.ps:
	latex $*.tex
	dvips $*.dvi


