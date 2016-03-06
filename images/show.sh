while true
do
    cat TIBLT001050_output.rgb > /dev/graphics/fb1
    sleep 3
    cat TIBLT002203_output.rgba > /dev/graphics/fb1
    sleep 3
    cat TIBLT002300_output.rgba > /dev/graphics/fb1
    sleep 3
    cat TIBLT002402_input.rgba > /dev/graphics/fb1
    sleep 3
done