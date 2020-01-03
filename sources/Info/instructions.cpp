#include "../../headers/Info/instructions.h"

/* implementation for basic constructor which allows to create the objects for this dialog window */
Instructions::Instructions(QDialog *parent) {
    // setting the fonts for labels
    this->boldItalicText.setBold(true);
    this->boldItalicText.setItalic(true);
    this->boldItalicText.setPointSize(16);

    this->boldNormalText.setBold(true);
    this->boldNormalText.setPointSize(14);

    // creating an object for main vertical layout
    this->mainVerticalLayout = new QVBoxLayout();

    // creating the new object for each label
    this->labelMainOptions = new QLabel(MAIN_OPTIONS);
    this->labelMainOptions->setFont(boldItalicText);

    this->labelAdditionalOptions = new QLabel(ADDITIONAL_OPTIONS);
    this->labelAdditionalOptions->setFont(boldItalicText);

    // label for HELP
    this->labelHelp = new QLabel("  • HELP --- " + HELP);
    this->labelHelp->setFont(boldNormalText);

    // label for EXIT
    this->labelExit = new QLabel("  • EXIT --- " + EXIT);
    this->labelExit->setFont(boldNormalText);

    // label for CLOSE
    this->labelClose = new QLabel("  • CLOSE --- " + CLOSE);
    this->labelClose->setFont(boldNormalText);

    // label for CLEAR
    this->labelClear = new QLabel("  • CLEAR --- " + CLEAR);
    this->labelClear->setFont(boldNormalText);

    // label for SHUFFLE
    this->labelShuffle = new QLabel("  • SHUFFLE --- " + SHUFFLE);
    this->labelShuffle->setFont(boldNormalText);

    // label for SAVE
    this->labelSave = new QLabel("  • SAVE --- " + SAVE);
    this->labelSave->setFont(boldNormalText);

    // label for OPEN
    this->labelOpen = new QLabel("  • OPEN --- " + OPEN);
    this->labelOpen->setFont(boldNormalText);

    // label for CALC
    this->labelCalc = new QLabel("  • CALC --- " + CALC);
    this->labelCalc->setFont(boldNormalText);

    // label for +
    this->labelPlus = new QLabel("  + " + PLUS);
    this->labelPlus->setFont(boldNormalText);

    // label for -
    this->labelMinus = new QLabel("  - " + MINUS);
    this->labelMinus->setFont(boldNormalText);

    // label for <-
    this->labelBackSpace = new QLabel("  <- " + BACKSPACE);
    this->labelBackSpace->setFont(boldNormalText);

    // adding labels to main vertical layout
    this->mainVerticalLayout->addWidget(labelMainOptions);
    this->mainVerticalLayout->addWidget(labelHelp);
    this->mainVerticalLayout->addWidget(labelExit);
    this->mainVerticalLayout->addWidget(labelClose);
    this->mainVerticalLayout->addWidget(labelClear);
    this->mainVerticalLayout->addWidget(labelShuffle);
    this->mainVerticalLayout->addWidget(labelSave);
    this->mainVerticalLayout->addWidget(labelOpen);
    this->mainVerticalLayout->addWidget(labelCalc);
    this->mainVerticalLayout->addWidget(labelAdditionalOptions);
    this->mainVerticalLayout->addWidget(labelPlus);
    this->mainVerticalLayout->addWidget(labelMinus);
    this->mainVerticalLayout->addWidget(labelBackSpace);

    // setting the main vertical layout as a main layout
    this->setLayout(mainVerticalLayout);
}

/* implementation for basic destructor which allows to free allocated memory for objects*/
Instructions::~Instructions() {
    delete mainVerticalLayout;
    delete labelMainOptions;
    delete labelAdditionalOptions;
    delete labelHelp;
    delete labelExit;
    delete labelClose;
    delete labelClear;
    delete labelShuffle;
    delete labelSave;
    delete labelOpen;
    delete labelCalc;
    delete labelPlus;
    delete labelMinus;
    delete labelBackSpace;
}

/* implementation for function which allows to start the demonstration of instructions */
void Instructions::showInstructions() {
    this->exec();
}