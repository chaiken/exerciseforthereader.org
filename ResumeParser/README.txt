ResumeParser Project
-----------------------

Last maintained: January 2010

Goal
-----

Create an easily maintainable resume database in XML that can be used to generate views of different output length, format (PDF,PS, .docx and xhtml) and emphasis (via runtime-selectable theming stored in attributes of elements).   Enable creation and maintenance of the database using an Eclipse RCP-based GUI.   Deploy to the masses and become rich and famous.


Warranty
---------

This source code was created by rabid chipmunks.   Expect the stability, security and performance that is usually associated with rabid-chipmunk-generated code.

But seriously, this code was created by a beginner for fun.    Please take it and render it useful if you are so inclined.

Installation
--------------

1. Download the archive and unzip it.

   tar -xjpf ResumeParser.tar.bz2
   cd ResumeParserPackage

2. Install Java if you don't have it.

3. Compile the java source with javac:

   javac ResumeParser.java

4. Test the parser installation by running the example:

   java ResumeParser exampleIn.xml XHTMLresumeAttributes.xsl exampleOut.xhtml

Creating the Data File
------------------------

1. Use a text editor (emacs, vim, mg . . .) or XML editor 


Running the Parser
-------------------

1. Execute the parser:

   java ResumeParser <YOUR NEW INPUT>.xml XHTMLresumeAttributes.xsl <YOUR NEW OUTPUT>.xhtml

2. Correct XML errors.   

3. Open the xhtml output with any browser to see if your data has rendered properly.

4. Click on the W3C icons at the bottom of the page to check its validity.


Test conditions
----------------

Fedora 12 through 14 using Java(TM) SE Runtime Environment (build 1.6.0_21-b06), xalan-j2-2.7.1 and various Firefoxen.


Future Features (Good Intentions)
------------------------------------

1. Refactor to support recursive process of elements with attributes for better performance.   (Works already for elements without attributes.)

2. Create Eclipse RCP stand-alone application with GUI interface to create XML file.

3. Support .docx, postscript and PDF output from the GUI using XSL-FO commands.

4. Deploy to Eclipse RCP applications website.


License
--------

GPLv3 or even better.


Resources
-----------

1. Eclipse RCP: http://www.eclipse.org/community/rcpos.php

2. IBM tutorial on recursion in XSL: http://www.ibm.com/developerworks/xml/library/x-xslrecur/

3. XSLT macros tutorial: http://lichteblau.blogspot.com/2007/07/macros-for-xslt.html

4.Tutorial on XPath and XSLT: http://www.w3schools.com/Xpath/xpath_functions.asp


Author
--------
 
Alison Chaiken, alchaiken@gmail.com, http://www.exerciseforthereader.org/
alisonchaiken on identi.ca
Alison_Chaiken on IRC
