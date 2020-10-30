#!/bin/bash

printf "Enter file name: "

read file_name

file_name="$(tr '[:lower:]' '[:upper:]' <<< ${file_name:0:1})${file_name:1}"

touch "./src/internal/public/$file_name.h"
touch "./src/internal/private/$file_name.cpp"

header="#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

class $file_name : public wxFrame
{
public:
    $file_name(const wxString& title);
};
"
source="#include \"../public/$file_name.h\"

$file_name::$file_name(const wxString& title)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(210, 110))
{
}
"

printf "$header" > "src/internal/public/$file_name.h"
printf "$source" > "src/internal/private/$file_name.cpp"

code "src/internal/public/$file_name.h"
code "src/internal/private/$file_name.cpp"