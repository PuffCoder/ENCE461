all: guide.pdf

%.pdf: %.tex hardware.tex software.tex troubleshooting.tex debugging.tex openocd.tex assessment.tex git.tex requirements.tex PCB.tex schematic.tex rework.tex schedule.tex firstprogram.tex testprograms.tex sleeping.tex EMC.tex libraries.tex application.tex introduction.tex pins.tex assembly.tex
	pdflatex -shell-escape $<
	pdflatex -shell-escape $<

figs/%.schtex: figs/*.sch
	schtex $< $@

clean:
	-rm -rf *.out *.aux *.log *.pdf *.toc _minted-guide

push:
	git push
