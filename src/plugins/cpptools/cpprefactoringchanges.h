/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (info@qt.nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at info@qt.nokia.com.
**
**************************************************************************/

#ifndef CPPREFACTORINGCHANGES_H
#define CPPREFACTORINGCHANGES_H

#include <ASTfwd.h>
#include <cplusplus/ModelManagerInterface.h>
#include <cplusplus/CppDocument.h>
#include <cplusplus/LookupContext.h>

#include <cpptools/cpptools_global.h>

#include <texteditor/refactoringchanges.h>

namespace CppTools {

class CppRefactoringChanges;

class CPPTOOLS_EXPORT CppRefactoringFile: public TextEditor::RefactoringFile
{
public:
    CppRefactoringFile();
    CppRefactoringFile(QTextDocument *document, const QString &fileName = QString());
    CppRefactoringFile(TextEditor::BaseTextEditorWidget *editor);

    CPlusPlus::Document::Ptr cppDocument() const;
    void setCppDocument(CPlusPlus::Document::Ptr document);

    CPlusPlus::Scope *scopeAt(unsigned index) const;

    bool isCursorOn(unsigned tokenIndex) const;
    bool isCursorOn(const CPlusPlus::AST *ast) const;

    Range range(int start, int end) const;
    Range range(unsigned tokenIndex) const;
    Range range(CPlusPlus::AST *ast) const;

    const CPlusPlus::Token &tokenAt(unsigned index) const;

    int startOf(unsigned index) const;
    int startOf(const CPlusPlus::AST *ast) const;
    int endOf(unsigned index) const;
    int endOf(const CPlusPlus::AST *ast) const;

    void startAndEndOf(unsigned index, int *start, int *end) const;

    using TextEditor::RefactoringFile::textOf;
    QString textOf(const CPlusPlus::AST *ast) const;

protected:
    CppRefactoringFile(const QString &fileName, CppRefactoringChanges *refactoringChanges);

private:
    CppRefactoringChanges *refactoringChanges() const;

    mutable CPlusPlus::Document::Ptr m_cppDocument;

    friend class CppRefactoringChanges; // for access to constructor
};

class CPPTOOLS_EXPORT CppRefactoringChanges: public TextEditor::RefactoringChanges
{
public:
    CppRefactoringChanges(const CPlusPlus::Snapshot &snapshot);

    const CPlusPlus::Snapshot &snapshot() const;
    CppRefactoringFile file(const QString &fileName);

private:
    virtual void indentSelection(const QTextCursor &selection,
                                 const QString &fileName,
                                 const TextEditor::BaseTextEditorWidget *textEditor) const;
    virtual void fileChanged(const QString &fileName);

private:
    CPlusPlus::Document::Ptr m_thisDocument;
    CPlusPlus::Snapshot m_snapshot;
    CPlusPlus::LookupContext m_context;
    CPlusPlus::CppModelManagerInterface *m_modelManager;
    CPlusPlus::CppModelManagerInterface::WorkingCopy m_workingCopy;
};

} // namespace CppTools

#endif // CPPREFACTORINGCHANGES_H
