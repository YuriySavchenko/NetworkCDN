#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <QDialog>
#include <QString>
#include <QLabel>
#include <QFont>
#include <QVBoxLayout>

const QString MAIN_OPTIONS="Controlling of the application is available by next commands:\n\n";

const QString HELP="command allows to print instructions of using the application.";
const QString EXIT="command allows to exit from the application.";
const QString CLOSE="command allows to close the graph.";
const QString CLEAR="command allows to reset all found paths on the graph.";
const QString SHUFFLE="command allows to shuffle all nodes on the graph.";
const QString SAVE="command allows to save all changes on the scene.";
const QString OPEN="command allows to upload the saved scene.";
const QString CALC="command allows to find the best path on the graph (enter nodes through comma: 1,7).";
const QString HISTOGRAM="command allows to create histogram which demonstrates metrics.";

const QString ADDITIONAL_OPTIONS="\n\nControlling of the application by additional commands:\n\n";

const QString PLUS="allows to zoom in the graph.";
const QString MINUS="allows to zoom out the graph.";
const QString BACKSPACE="allows to delete uncorrect word that you wrote.";

//!
//! \brief The Instructions class\n
//! \b Instructions it's special class which allows
//! print \a rules how to control an \a application.
//!
class Instructions : public QDialog {
public:
    Instructions(QDialog *parent = nullptr);    //!< A typicall \e constructor
    ~Instructions();                            //!< A typicall \e destructor

public:
    void showInstructions();                    //!< A \e functions which allows to start an \e execution of \a window with \b Instructions

public:
    QFont boldItalicText;                       //!< A combination of \e Bold and \e Italic \b Font for \a text
    QFont boldNormalText;                       //!< A combination of \e Bold and \e Normal \b Font for \a text

    QVBoxLayout *mainVerticalLayout;            //!< A \b mainVerticalLayout \a variable which allows to save other \e layouts

    QLabel *labelMainOptions;                   //!< A \a label for demonstration \b MainOptions
    QLabel *labelAdditionalOptions;             //!< A \a label for demonstration \b AdditionalOptions

    QLabel *labelHelp;                          //!< A \a label for demonstration \b Help \e command
    QLabel *labelExit;                          //!< A \a label for demonstration \b Exit \e command
    QLabel *labelClose;                         //!< A \a label for demonstration \b Close \e command
    QLabel *labelClear;                         //!< A \a label for demonstration \b Clear \e command
    QLabel *labelShuffle;                       //!< A \a label for demonstration \b Shuffle \e command
    QLabel *labelSave;                          //!< A \a label for demonstration \b Save \e command
    QLabel *labelOpen;                          //!< A \a label for demonstration \b Open \e command
    QLabel *labelCalc;                          //!< A \a label for demonstration \b Calc \e command
    QLabel *labelHistogram;                     //!< A \a label for demonstration \b Histogram command

    QLabel *labelPlus;                          //!< A \a label for demonstration \b + \e command
    QLabel *labelMinus;                         //!< A \a label for demonstration \b - \e command
    QLabel *labelBackSpace;                     //!< A \a label for demonstration \b <- \e command
};

#endif // INSTRUCTIONS_H