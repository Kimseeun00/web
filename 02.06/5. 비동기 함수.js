console.log("hi");

setTimeout(() => {
    console.log(1);
    setTimeout(() =>{
        console.log(2);
        setTimeout(() => {
            console.log(3);
        })
    },1000)
},500)