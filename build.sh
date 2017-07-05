#!/bin/bash

# dependency: GraphViz, inkscape, TexLive 2016,

function img
{
    dotsrcs=(`find image/ -iname '*.dot' | sed 's/\.dot//g'`)
    svgimages=(`find image/ -iname '*.svg' | sed 's/\.svg//g'`)
    svgcount=${#svgimages[@]}
    
    for (( i=0; i<${svgcount}; i++ ));
    do
        srcimg="${svgimages[$i]}.svg"
        dstimg="${svgimages[$i]}.pdf"
	echo "${srcimg} -> ${dstimg}"
        if [[ "${srcimg}" -nt "${dstimg}" ]]; then
            inkscape -D -z -f "${srcimg}" -A "${dstimg}"
        fi
    done

    dotcount=${#dotsrcs[@]}
    for (( i=0; i<${dotcount}; i++ ));
    do
        srcimg="${dotsrcs[$i]}.dot"
        tmpimg="${dotsrcs[$i]}.svg"
        dstimg="${dotsrcs[$i]}.pdf"
	echo "${srcimg} -> ${dstimg}"
        if [[ "${srcimg}" -nt "${dstimg}" ]]; then
            dot -T svg -o "${tmpimg}" "${srcimg}"
            inkscape -D -z -f "${tmpimg}" -A "${dstimg}"
            rm -f "${tmpimg}"
        fi
    done
    
}

function build
{    
    latexmk $@ -pdf main.tex
}

function clean
{
    rm -f image/*.pdf
    latexmk -c
}

#################### main ##################

case $1 in
    clean)
        clean
        ;;
    live)
        img
        build -pvc -interaction=nonstopmode
        ;;
    image)
        img
	;;
    *)
        img
        build $@
        ;;
esac

