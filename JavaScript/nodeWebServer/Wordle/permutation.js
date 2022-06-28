
const e = require('express');
const fetch = (...args) =>
import('node-fetch').then(({ default: fetch }) => fetch(...args));

let url = "https://api.dictionaryapi.dev/api/v2/entries/en/";

let setting = {method: "Get"};







printPerms('lab');

function printPerms(str){
    premutations(str,"");
}

 function premutations(str, prefix){
    if(str.length === 0){
        checkDick(prefix);
        //console.log(prefix + " ");
        return;
    }
    
    for(let i = 0;i < str.length; ++i){
        //console.log(result.substr(0,i) + result.substr(i + 1,len));
        let remainder = str.substring(0,i)+str.substring(i+1);
        premutations(remainder, prefix + str[i]);
    }
 }

 function checkDick(check){
   

    let perm = url.concat(check);
    fetch(perm,setting).then( res => res.json()).then((json) => {
        var words = json.word;
        var jsonArray = JSON.parse(JSON.stringify(words));
        
        jsonArray.forEach(element => {
        console.log(element);
        }); 

    });
 }