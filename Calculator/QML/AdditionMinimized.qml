import QtQuick 2.12
import com.malamute.calculator 1.0

TwoToOneTemplate
{
    Connections
    {
        target: idea
        function onDisplay(inputNumber1, inputNumber2, outputNumber)
        {
            input1Text = "<font color=\"" + idea.inPortLabelColors[0] + "\">" +
                    parseFloat(inputNumber1.toPrecision(4)) + "</font>";
            input2Text = "+ <font color=\"" + idea.inPortLabelColors[1] + "\">" +
                     + parseFloat(inputNumber2.toPrecision(4)) + "</font>";
            outputText = "= <font color=\"" + idea.outPortLabelColors[0] + "\">"
                    + parseFloat(outputNumber.toPrecision(4)) + "</font>";
        }
        function onClear()
        {
            input1Text = "";
            input2Text = "+ ";
            outputText = "= ";
        }
    }
}



