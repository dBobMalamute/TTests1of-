function createBoxes(inputNumber1, inputNumber2, outputNumber)
{
    let borderWidth
    let spacing;
    let xBoxNum;

    let boxComponent;
    let boxObject;

    let wholeBoxes = Math.ceil(inputNumber1) + Math.ceil(inputNumber2);
    let fadeInTime = 400 * Math.floor(Math.log2(wholeBoxes))

    if(wholeBoxes <= 6)
    {
        borderWidth = 8;
        spacing = 80;
        xBoxNum = 5;
    }
    else if(wholeBoxes <= 40)
    {
        borderWidth = 4;
        spacing = 40;
        xBoxNum = 10;
    }
    else if(wholeBoxes <= 160)
    {
        borderWidth = 2;
        spacing = 20;
        xBoxNum = 20;
    }
    else if (wholeBoxes <= 720)
    {
        borderWidth = 1;
        spacing = 10;
        xBoxNum = 40;
    }
    else if (wholeBoxes <= 4000)
    {
        borderWidth = 0;
        spacing = 4;
        xBoxNum = 100;
    }
    else if (wholeBoxes <= 20000)
    {
        borderWidth = 0;
        spacing = 2;
        xBoxNum = 200;
    }

    let i =0;
    // Add in the whole boxes for input1.
    for(i = 0; i < Math.floor(inputNumber1); i++)
    {
        boxComponent = Qt.createComponent("AdditionBox.qml");
        boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                  boxNumber: i, totalBoxes: wholeBoxes, fadeInTime: fadeInTime,
                                                  initialPoint: Qt.point(spacing*(i%xBoxNum) + 0.5,
                                                                         spacing*Math.floor((i/xBoxNum)) + 0.5),
                                                  finalPoint: Qt.point(399.5 - spacing - spacing*(i%xBoxNum),
                                                                       spacing*Math.floor((i/xBoxNum)) + 0.5),
                                                  width: spacing - 1, height: spacing - 1,
                                                  initialColor: idea.inPortLabelColors[0],
                                                  finalColor: idea.outPortLabelColors[0]})
    }

    // Add in the whole boxes for input2.
    for(i = 0; i < Math.floor(inputNumber2); i++)
    {
        boxComponent = Qt.createComponent("AdditionBox.qml");
        boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                  boxNumber: Math.floor(inputNumber1) + i, totalBoxes: wholeBoxes, fadeInTime: fadeInTime,
                                                  initialPoint: Qt.point(spacing*(i%xBoxNum) + 0.5,
                                                                         199.5 - spacing - spacing*Math.floor((i/xBoxNum))),
                                                  finalPoint: Qt.point(399.5 - spacing - spacing*((i+Math.floor(inputNumber1))%xBoxNum),
                                                                       spacing*Math.floor(((i + Math.floor(inputNumber1))/xBoxNum)) + 0.5),
                                                  width: spacing - 1, height: spacing - 1,
                                                  initialColor: idea.inPortLabelColors[1],
                                                  finalColor: idea.outPortLabelColors[0]})
    }

    //Handle the extra fractions. If there are any
    if((inputNumber1 % 1.0) !== 0 && (inputNumber2 % 1.0) !== 0)
    {
        //2 fractional components.
        let frac1 = (inputNumber1 % 1.0);
        let frac2 = (inputNumber2 % 1.0);
        let box1Final;
        let box2Final;
        if(frac1 + frac2 < 1.0)
        {
            box1Final = frac1 + frac2;
            box2Final = 0.0;
        }
        else
        {
            box1Final = 1.0;
            box2Final = frac1 + frac2 - 1.0;
        }
        boxComponent = Qt.createComponent("AdditionBox.qml");
        boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                  boxNumber: Math.floor(inputNumber1), totalBoxes: wholeBoxes, fadeInTime: fadeInTime,
                                                  initialPoint: Qt.point(spacing*(Math.floor(inputNumber1)%xBoxNum) + 0.5,
                                                                         spacing*Math.floor((Math.floor(inputNumber1)/xBoxNum)) + 0.5),
                                                  finalPoint: Qt.point(399.5 - box1Final * (spacing - 1.0) - 1 - spacing*((Math.floor(inputNumber2)+Math.floor(inputNumber1))%xBoxNum),
                                                                       spacing*Math.floor(((Math.floor(inputNumber2) + Math.floor(inputNumber1))/xBoxNum)) + 0.5),
                                                  width: (spacing - 1) * (inputNumber1 % 1.0), height: spacing - 1,
                                                  initialColor: idea.inPortLabelColors[0],
                                                  finalColor: idea.outPortLabelColors[0],
                                                  initialWidth: (spacing - 1) * (inputNumber1 % 1.0),
                                                  finalWidth: box1Final * (spacing - 1.0)})

        boxComponent = Qt.createComponent("AdditionBox.qml");
        boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                  boxNumber: Math.floor(inputNumber1) + Math.floor(inputNumber2), totalBoxes: wholeBoxes, fadeInTime: fadeInTime,
                                                  initialPoint: Qt.point(spacing*(Math.floor(inputNumber2)%xBoxNum) + 0.5,
                                                                         199.5 - spacing - spacing*Math.floor((Math.floor(inputNumber2)/xBoxNum))),
                                                  finalPoint: Qt.point(399.5 - box2Final * (spacing - 1.0) - 1 - spacing*((Math.floor(inputNumber2)+Math.floor(inputNumber1) + 1)%xBoxNum),
                                                                       spacing*Math.floor(((Math.floor(inputNumber2) + Math.floor(inputNumber1) + 1)/xBoxNum)) + 0.5),
                                                  width: (spacing - 1) * (inputNumber2 % 1.0), height: spacing - 1,
                                                  initialColor: idea.inPortLabelColors[1],
                                                  finalColor: idea.outPortLabelColors[0],
                                                  initialWidth: (spacing - 1) * (inputNumber2 % 1.0),
                                                  finalWidth: box2Final * (spacing - 1.0)})

    }
    else if((inputNumber1 % 1.0) !== 0)
    {
        //Only a fractional component in input 1.
        boxComponent = Qt.createComponent("AdditionBox.qml");
        boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                  boxNumber: Math.floor(inputNumber1), totalBoxes: wholeBoxes, fadeInTime: fadeInTime,
                                                  initialPoint: Qt.point(spacing*(Math.floor(inputNumber1)%xBoxNum) + 0.5,
                                                                         spacing*Math.floor((Math.floor(inputNumber1)/xBoxNum)) + 0.5),
                                                  finalPoint: Qt.point(399.5 - (spacing - 1) * (inputNumber1 % 1.0) - 1 - spacing*((Math.floor(inputNumber2)+Math.floor(inputNumber1))%xBoxNum),
                                                                       spacing*Math.floor(((Math.floor(inputNumber2) + Math.floor(inputNumber1))/xBoxNum)) + 0.5),
                                                  width: (spacing - 1) * (inputNumber1 % 1.0), height: spacing - 1,
                                                  initialColor: idea.inPortLabelColors[0],
                                                  finalColor: idea.outPortLabelColors[0]})
    }
    else if((inputNumber2 % 1.0) !== 0)
    {
        //Only a fractional component in input 2.
        boxComponent = Qt.createComponent("AdditionBox.qml");
        boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                  boxNumber: Math.floor(inputNumber1) + Math.floor(inputNumber2), totalBoxes: wholeBoxes, fadeInTime: fadeInTime,
                                                  initialPoint: Qt.point(spacing*(Math.floor(inputNumber2)%xBoxNum) + 0.5,
                                                                         199.5 - spacing - spacing*Math.floor((Math.floor(inputNumber2)/xBoxNum))),
                                                  finalPoint: Qt.point(399.5 - (spacing - 1) * (inputNumber2 % 1.0) - 1 - spacing*((Math.floor(inputNumber2)+Math.floor(inputNumber1))%xBoxNum),
                                                                       spacing*Math.floor(((Math.floor(inputNumber2) + Math.floor(inputNumber1))/xBoxNum)) + 0.5),
                                                  width: (spacing - 1) * (inputNumber2 % 1.0), height: spacing - 1,
                                                  initialColor: idea.inPortLabelColors[1],
                                                  finalColor: idea.outPortLabelColors[0]})
    }
}

function add()
{
    for(let i = 0; i < animationArea.children.length; i++)
    {
        animationArea.children[i].animate();
    }
}

function reset()
{
    for(let i = 0; i < animationArea.children.length; i++)
    {
        animationArea.children[i].reset();
    }
}

function clearBoxes()
{
    for(let i = 0; i < animationArea.children.length; i++)
    {
        animationArea.children[i].destroy();
    }
}
