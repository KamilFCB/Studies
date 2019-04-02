module.exports = {
    Foo : function(){
        console.log('Moduł B');
        var moduleA = require('./zad4_moduleA.js');
        moduleA.Bar();
    },
    Bar : function(){
        console.log("Wywołanie z modułu A");
    }
}