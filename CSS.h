#pragma once

const char CSS[] PROGMEM = R"(
* { 
    font-family: Arial, Helvetica;
  }
  body{
    margin:0;
  }
  h1{
    background-color: #fafafa;
    margin: 0px;
    padding: 10px 8px;
  }
  h1 a{
    text-decoration:none;
    color:#000000;
  }
  fieldset {
    background-color: #fdfdfd;
    max-width:500px;
  }
  ul.navi{ 
    float: left;
    position: fixed;
    height: 100%;
    width: 140px;
    margin-block-start: 0em;
    margin-block-end: 0em;
    margin-inline-start: 0px;
    margin-inline-end: 0px;
    padding-inline-start: 0px;
    padding:2px;
    background-color: #dcf1e3ad;
  }
  
  form{
    /*width : 400px;*/
  }
  #projectLink{
    font-size : 8pt;
  }

  .navi li {
    display: block;
    background-color: #cccccc;
    padding: 1px;
    font-weight:bold;
    margin:2px;
  }

  #main{
    margin:2px;
    margin-left: 145px;
    padding:3px;
    /*border:black 1px solid; */
  }

  #footer {
    position: fixed;
    left: 0;
    bottom: 0;
    width: 100%;
    text-align: center;
  }

  label{
    width: 120;
    display: inline-block;
  }
)";
