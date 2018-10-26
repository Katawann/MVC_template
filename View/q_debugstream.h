/** source:  http://www.qtforum.org/article/39768/redirecting-std-cout-std-cerf-qdebug-to-qtextedit.html */

#ifndef Q_DEBUGSTREAM_H
#define Q_DEBUGSTREAM_H

#include <QObject>
#include "view.h"
#include <iostream>
#include <streambuf>
#include <string>

class MessageOutput: public QObject{

    Q_OBJECT

private:
    View* view;

public:

    MessageOutput( View* view, string type){

        if (type == "console") {
            connect( this, SIGNAL(sendText_append(QString)),
                     view->getConsole(), SLOT(append(QString)) );
            connect( this, SIGNAL(sendText_consoleText(QString)),
                     view->getConsole(), SLOT(insertPlainText(QString)) );
            connect( this, SIGNAL(deleteLastLine()),
                     view->getConsole(), SLOT(undo()) );

        }else if (type == "error"){
            connect( this, SIGNAL(sendText_append(QString)),
                     view, SLOT(errorMessage(QString)) );
            connect( this, SIGNAL(sendText_consoleText(QString)),
                     view, SLOT(errorMessage(QString)) );
        }else{
            cerr << "The type " << type << " is not defined for redirection of stream" << endl;
        }
    }

    ~MessageOutput(){
    }

    void append(QString _msg){
        emit sendText_append(_msg);
    }

    void insertPlainText(QString _msg){
        emit sendText_consoleText(_msg);
    }

    void deleteLine(){
        emit deleteLastLine();
    }

signals:
    void sendText_append(QString);
    void sendText_consoleText(QString);
    void deleteLastLine();
};

class Q_DebugStream : public std::basic_streambuf<char>
{

private:
    std::ostream &m_stream;
    std::streambuf *m_old_buf;
    MessageOutput* log_text;

public:

    Q_DebugStream(std::ostream &stream, View* text_edit, string type) : m_stream(stream)
    {
        log_text = new MessageOutput(text_edit ,type);
        m_old_buf = stream.rdbuf();
        stream.rdbuf(this);
    }

    ~Q_DebugStream()
    {
        delete log_text;
        m_stream.rdbuf(m_old_buf);
    }


protected:

    //This is called when a std::endl has been inserted into the stream
    //or a special character
    virtual int_type overflow(int_type v)
    {
        if (v == '\n'){
            log_text->append("");
        }else if (v == '\b'){
            cout << ".";
            log_text->deleteLine();
        }else{
            //convert the special character ASCII in a char and send it to QTextEdit
            //(necessary for number)
            QString str( std::char_traits<char_type>::to_char_type(v) );
            log_text->insertPlainText(str);
        }

        return v;
    }

    virtual std::streamsize xsputn(const char *p, std::streamsize n)
    {
        QString str(p);
        if(str.contains("\n")){
            QStringList strSplitted = str.split("\n");
            log_text->insertPlainText (strSplitted.at(0)); //Index 0 is still on the same old line

            for(int i = 1; i < strSplitted.size(); i++){
                log_text->append(strSplitted.at(i));
            }

        }else{
            log_text->insertPlainText (str);
        }
        return n;
    }
};


#endif // Q_DEBUGSTREAM_H
