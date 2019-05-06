
(() => {
var addon = require('bindings')('addon');
const fs = require('fs');
let string_incoming_value;

fs.readFile(__dirname+'/hw8input.txt', "utf8", (err, data) => {
    if(err){console.log(err);}else{
        data = data.split("\n");
        string_incoming_value = data;
        string_incoming_value = JSON.stringify(string_incoming_value);
    }
});


let longestword = ((strsplit) =>{
let largestwordlist;
let returnarray = [];
largestwordlist = strsplit.sort((a,b) => {
return b.length - a.length;
});

for(let i = 0; i < 10; i++){
returnarray[i] = largestwordlist[i];
}
return returnarray;
});

setTimeout(() => {
var obj = new addon.MyObject(10);
let sanitizedarray = string_incoming_value.split(" ");
let return_longestword;

return_longestword = longestword(sanitizedarray);

//------------------------------------------------
console.log("outputting javascript: ");
console.log(" ");
for(let key in return_longestword){
    console.log(return_longestword[key]);
}
console.log(return_longestword.length);


console.log(" ");
console.log(" ");
console.log(" ");

console.log("outputting C++ text");
let outval_array = [];


    outval_array = obj.longest(sanitizedarray);

for(let key in outval_array){
    console.log(outval_array[key]);
}
//var obj = new addon.MyObject([10, 20, 30, 50], 4);
//obj.printArr();


//var obj = new addon.MyObject(10);
}, 1000);


})();