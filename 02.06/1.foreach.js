
let pplus = [];
let mminus = [];
//const array = [-5,3,4,2,-7,-2,7];
array.forEach((value) => {
    if(value > 0){
        pplus.push(value);
    }
    if(value < 0){
        mminus.push(value);
    }
  return;
});

const array = [1,2,3,4,5];

array.every(el => el > 0);

const inventory = [
    {name:"A", count : 1},
    {name:"B", count : 2},
    {name:"C", count : 3}
];

// 특정 조건을 만족하는 첫번재 값
inventory.find (el => el.name ==="B");


//findIndex 특정 조건을 만족하는 첫번재 인덱스  찾아옴


const chicken = [
    {name: "머리", quantity : 1},
    {name: "날개", quantity : 2},
    {name: "닭다리", quantity : 2},
    {name: "닭가슴살", quantity : 1},
    {name: "닭발", quantity : 2},
];

chicken.findIndex(el => el.name === "닭다리");