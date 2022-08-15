function createBoxes(inputNumber1, inputNumber2, outputNumber)
{
    let borderWidth
    let spacing;
    let xBoxNum;

    let boxComponent;
    let boxObject;

    let totalBoxes = Math.ceil(inputNumber1) + Math.ceil(inputNumber2);

    let col0 = idea.inPortLabelColors[0];
    let col1 = idea.inPortLabelColors[1];
    let col2 = Qt.rgba(1,1,1,0.0)

    if(inputNumber1 <= 5 && inputNumber2 <= 2)
    {
        spacing = 80;
        borderWidth = 8;
        xBoxNum = 5;
    }
    else if(inputNumber1 <= 10 && inputNumber2 <= 5)
    {
        spacing = 40;
        borderWidth = 4;
        xBoxNum = 10;
    }
    else if(inputNumber1 <= 20 && inputNumber2 <= 10)
    {
        spacing = 20;
        borderWidth = 2;
        xBoxNum = 20;
    }
    else if(inputNumber1 <= 40 && inputNumber2 <= 20)
    {
        spacing = 10;
        borderWidth = 1;
        xBoxNum = 40;
    }
    else if(inputNumber1 <= 100 && inputNumber2 <= 50)
    {
        spacing = 4;
        borderWidth = 0;
        xBoxNum = 100;
    }
    else if(inputNumber1 <= 200 && inputNumber2 <= 100)
    {
        spacing = 2;
        borderWidth = 0;
        xBoxNum = 200;
    }

    let fadeInTime = 800 * Math.floor(Math.log2(totalBoxes + 3))

    let i = 0;
    for(i = 0; i < Math.floor(inputNumber1); i++)
    {
        boxComponent = Qt.createComponent("MultiplicationBox.qml");
        boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                  boxNumber: i, totalBoxes: totalBoxes, fadeInTime: fadeInTime,
                                                  initialRect: Qt.rect(spacing*i + 0.5,
                                                                         0.5, spacing - 1.0, spacing - 1.0),
                                                  initialColor: col0,
                                                  finalColor: idea.outPortLabelColors[0]})
    }


    for(i = 0; i < Math.floor(inputNumber2); i++)
    {
        boxComponent = Qt.createComponent("MultiplicationBox.qml");
        boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                  boxNumber: Math.floor(inputNumber1) + i + 2, totalBoxes: totalBoxes, fadeInTime: fadeInTime,
                                                  initialRect: Qt.rect(0.5,
                                                                         spacing*i + 0.5, spacing - 1.0, spacing - 1.0),
                                                  initialColor: col1,
                                                  finalColor: idea.outPortLabelColors[0]})
    }

    let numBoxesToAdd = ((Math.floor(inputNumber1)*Math.floor(inputNumber2)) - Math.floor(inputNumber1) - Math.floor(inputNumber2)) + 1;
    console.log("Num: " + numBoxesToAdd)
    for(i = 0; i < numBoxesToAdd; i++)
    {
        boxComponent = Qt.createComponent("MultiplicationBox.qml");
        boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                  boxNumber: Math.floor(inputNumber1) + i, totalBoxes: totalBoxes, fadeInTime: fadeInTime,
                                                  initialRect: Qt.rect((i%(Math.floor(inputNumber1) - 1)) * spacing + spacing + 0.5,
                                                                        Math.floor(i/(Math.floor(inputNumber1) - 1)) * spacing + spacing + 0.5,
                                                                       spacing - 1.0, spacing - 1.0),
                                                  initialColor: col2,
                                                  finalColor: idea.outPortLabelColors[0]})
    }
    if((inputNumber1 % 1.0) !== 0) // Fraction input1.
    {
        boxComponent = Qt.createComponent("MultiplicationBox.qml");
        boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                  boxNumber: Math.floor(inputNumber1) + 1, totalBoxes: totalBoxes, fadeInTime: fadeInTime,
                                                  initialRect: Qt.rect(spacing*Math.floor(inputNumber1) + 0.5,
                                                                         0.5, (spacing - 1.0) * (inputNumber1 % 1.0), spacing - 1.0),
                                                  initialColor: col0,
                                                  finalColor: idea.outPortLabelColors[0]})

        for(i = 1; i < Math.floor(inputNumber2); i++)
        {
            boxComponent = Qt.createComponent("MultiplicationBox.qml");
            boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                      boxNumber: Math.floor(inputNumber1), totalBoxes: totalBoxes, fadeInTime: fadeInTime,
                                                      initialRect: Qt.rect(spacing*Math.floor(inputNumber1) + 0.5,
                                                                             0.5 + spacing*i, (spacing - 1.0) * (inputNumber1 % 1.0), spacing - 1.0),
                                                      initialColor: col2,
                                                      finalColor: idea.outPortLabelColors[0]})
        }

    }
    if((inputNumber2 % 1.0) !== 0) // Need a fraction box for input 1.
    {
        boxComponent = Qt.createComponent("MultiplicationBox.qml");
        boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                  boxNumber: Math.floor(inputNumber1) + Math.floor(inputNumber2) + 3, totalBoxes: totalBoxes, fadeInTime: fadeInTime,
                                                  initialRect: Qt.rect(0.5,
                                                                         spacing*Math.floor(inputNumber2) + 0.5, spacing - 1.0, (spacing - 1.0) * (inputNumber2 % 1.0)),
                                                  initialColor: col1,
                                                  finalColor: idea.outPortLabelColors[0]})

        for(i = 1; i < Math.floor(inputNumber1); i++)
        {
            boxComponent = Qt.createComponent("MultiplicationBox.qml");
            boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                      boxNumber: Math.floor(inputNumber1) + Math.floor(inputNumber2), totalBoxes: totalBoxes, fadeInTime: fadeInTime,
                                                      initialRect: Qt.rect(0.5 + spacing*i, spacing*Math.floor(inputNumber2) + 0.5,
                                                                           spacing - 1.0, (spacing - 1.0) * (inputNumber2 % 1.0)),
                                                      initialColor: col2,
                                                      finalColor: idea.outPortLabelColors[0]})
        }
    }
    if((inputNumber1 % 1.0) !== 0 && (inputNumber2 % 1.0) !== 0)
    {
        boxComponent = Qt.createComponent("MultiplicationBox.qml");
        boxObject = boxComponent.createObject(animationArea, {borderWidth: borderWidth,
                                                  boxNumber: Math.floor(inputNumber1) + Math.floor(inputNumber2), totalBoxes: totalBoxes, fadeInTime: fadeInTime,
                                                  initialRect: Qt.rect(spacing*Math.floor(inputNumber1) + 0.5, spacing*Math.floor(inputNumber2) + 0.5,
                                                                       (spacing - 1.0) * (inputNumber1 % 1.0), (spacing - 1.0) * (inputNumber2 % 1.0)),
                                                  initialColor: col2,
                                                  finalColor: idea.outPortLabelColors[0]})
    }
}

function multiply()
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
