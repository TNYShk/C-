
const e = require('express');
const fs = require('fs');

const fetch = (...args) =>
import('node-fetch').then(({ default: fetch }) => fetch(...args));

let url = "http://www.mocky.io/v2/5c3c7ad13100007400a1a401";

let setting = {method: "Get"};


fetch(url,setting).then( res => res.json()).then((json) => {
   
    var sorting = json.nodes.sort(sortByProperty("parent"));
    var jsonArray = JSON.parse(JSON.stringify(sorting));
    var prop = json.nodes.length;
  
    //walk(jsonArray);
  
  
     jsonArray.forEach(element => {
       // walk(element);
        //console.log(element.id + " " + element.text);
    }); 
    //console.log(jsonArray[56].id);
  
   
  
    writeItFile(sorting);

    //console.log(sorting);
    //writeItFile(json);
   
    
    
});
printPerms('lab');


var indent = 1;
function walk(tree) {
   
	tree.forEach(node => {
		console.log('--' + Array(indent).join('--'), node.text);
		if(node.id) {
			indent ++;
			walk(node.id);
		}
		if(tree.indexOf(node) === tree.length - 1) {
			indent--;
		}
	})
}


function wa1k(tree){
    var indent = 1;
    function levelWalk(tree){
        tree.forEach(function(node){
            console.log('--'+ Array(indent).join('--'), node.text);
            if(node.id){
                indent++;
                levelWalk(node.id);
            }
            if(tree.indexOf(node) === tree.length -1){
                indent --;
            }
        })
    }
    levelWalk(tree);
}

function writeItFile(data){
    fs.writeFile('./nodes1.json', JSON.stringify(data), function (err) {
        if (err){
            console.log("error happend!");
            return console.log(err);
        }
        console.log("worked?");
       
    })
}

function sortByProperty(property){  
    return function(a,b){  
       if(a[property] > b[property])  
          return 1;  
       else if(a[property] < b[property])  
          return  -1;  
   
       return 0;  
    }  
 }


function printPerms(str){
    premutations(str,"");
}

 function premutations(str, prefix){
    if(str.length === 0){
        console.log(prefix + " ");
        return;
    }
    
    for(let i = 0;i < str.length; ++i){
        //console.log(result.substr(0,i) + result.substr(i + 1,len));
        let remainder = str.substring(0,i)+str.substring(i+1);
        premutations(remainder, prefix + str[i]);
    }
 }



