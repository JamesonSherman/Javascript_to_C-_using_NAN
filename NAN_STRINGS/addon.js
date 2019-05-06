var addon = require('bindings')('addon');


const fs = require('fs')
let string_incoming_value;
fs.readFile(__dirname+'/hw8input.txt', "utf8", (err, data) => {
if(err){console.log(err);}else{
    data = data.split("\n");
    string_incoming_value = data;
    string_incoming_value = JSON.stringify(string_incoming_value);
}
});

let Modulus_Multiplcation = (has_uppervalues) =>{
    let converted_bool_array = [];
    let randomized_value_array = [];
    let integer ;


    for(let key in has_uppervalues){
    integer = has_uppervalues ? 1 : 0;
    converted_bool_array.push(integer);
    }

    for(let key in converted_bool_array){
        let increment = 0;
        let mod_key = 0;
        let pre_mod = 0;
        while(increment < 6){
            if(mod_key < 1){
                pre_mod = Math.floor(Math.random() *  1000) * converted_bool_array[key];
                mod_key++;
                increment++;
            } else {
                pre_mod = Math.floor(Math.random() * pre_mod);
                increment++;
            }
        }
        randomized_value_array.push(pre_mod % 27);
    }

    return randomized_value_array;
}

var hasLower = (instring, filter) => {
    let temparr = [];
    temparr = (filter == undefined ? filter = "" : filter.match(/./g))
    filter == "" ? temparr = [true] : temparr.forEach((element,idx) => { temparr[idx] = instring.includes(element); })
    return (/[a-z]/g.test(instring))&&temparr.reduce((acc, curr)=>{ return acc && curr });
}

setTimeout(() => {
    // holding arrays
    let Upper_Case_Letters = [];
    let has_uppercase_value = [];
    let base_10_output_array =[];
    let modulo_case_findupper_array = [];
    let lower_array = [];
    let second_peram;
//string value slicing    
string_incoming_value = string_incoming_value.split(" ");
string_incoming_value.shift();
//------------------------------------------------
//base object decleration
var obj = new addon.MyObject(10);
//------------------------------------------------
//iterative feed to c++
for(let key in string_incoming_value){
    Upper_Case_Letters.push(obj.findUpper(string_incoming_value[key]));
    has_uppercase_value.push(obj.hasUpper(string_incoming_value[key]));
    lower_array.push(obj.findLower(hasLower,string_incoming_value[key],""));
}
//scrubbing the whitespace
Upper_Case_Letters = Upper_Case_Letters.filter((str)=>{
return /\S/.test(str)
});
//-----------------------------------------------



base_10_output_array = Modulus_Multiplcation(has_uppercase_value);

for(let key in base_10_output_array){
    console.log(base_10_output_array[key]);
}
// let second_peram;
console.log(string_incoming_value.length);
console.log(base_10_output_array.length);

for(let key in string_incoming_value){
    if(base_10_output_array[key] >= 26){
        modulo_case_findupper_array.push(obj.findUpper(string_incoming_value[key]));
    }else{
        if(base_10_output_array[key] === 0){
            second_peram = 'A';
        }else if(base_10_output_array[key] === 1){
            second_peram = 'B';
        }else if (base_10_output_array[key] === 2){
            second_peram = 'C';
        }else if (base_10_output_array[key] === 3){
            second_peram = 'D';
        }else if (base_10_output_array[key] === 4){
            second_peram = 'E';
        }else if (base_10_output_array[key] === 5){
            second_peram = 'F';
        }else if (base_10_output_array[key] === 6){
            second_peram = 'G';
        }else if (base_10_output_array[key] === 7){
            second_peram = 'H';
        }else if (base_10_output_array[key] === 8){
            second_peram = 'I';
        }else if (base_10_output_array[key] === 9){
            second_peram = 'J';
        }else if (base_10_output_array[key] === 10){
            second_peram = 'K';
        }else if (base_10_output_array[key] === 11){
            second_peram = 'L';
        }else if (base_10_output_array[key] === 12){
            second_peram = 'M';
        }else if (base_10_output_array[key] === 13){
            second_peram = 'N';
        }else if (base_10_output_array[key] === 14){
            second_peram = 'O';
        }else if (base_10_output_array[key] === 15){
            second_peram = 'P';
        }else if (base_10_output_array[key] === 16){
            second_peram = 'Q';
        }else if (base_10_output_array[key] === 17){
            second_peram = 'R';
        }else if (base_10_output_array[key] === 18){
            second_peram = 'S';
        }else if (base_10_output_array[key] === 19){
            second_peram = 'T';
        }else if (base_10_output_array[key] === 20){
            second_peram = 'U';
        }else if (base_10_output_array[key] === 21){
            second_peram = 'V';
        }else if (base_10_output_array[key] === 22){
            second_peram = 'W';
        }else if (base_10_output_array[key] === 23){
            second_peram = 'X';
        }else if (base_10_output_array[key] === 24){
            second_peram = 'Y';
        }else {
            second_peram = 'Z';
        }    
        modulo_case_findupper_array.push(obj.findUpper(string_incoming_value[key]), second_peram);
    }
}

modulo_case_findupper_array = modulo_case_findupper_array.filter((str)=>{
    return /\S/.test(str)
    });

for(let key in Upper_Case_Letters){
    console.log(Upper_Case_Letters[key]);
}

for(let key in lower_array){
    console.log(lower_array[key]);
}

for(let key in modulo_case_findupper_array){
    console.log(modulo_case_findupper_array[key]);
}

//write files
fs.writeFile('Uppercase_Letters.txt', Upper_Case_Letters, (err) =>{
    if (err) throw err;
    console.log('Saved');
});

fs.writeFile('Lowercase.txt', lower_array, (err) => {
    if (err) throw err;
    console.log('Saved');
});

fs.writeFile('modulo_case.txt', modulo_case_findupper_array, (err)=>{
    if(err) throw err;
    console.log('Saved');
})
}, 1000);