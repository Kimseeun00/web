//const arr = [1,2,3,4,5,6];
//const newarr = arr.map((data) => data + 1);

// 원본 배열을 손상시키지 않으면서 새로운 배열을 만들어 가져옴

const arr = [1,2,3,4,5];
const newarr = arr.map((data) => data *data);

const arr2 = ["a","bcd","ef","g"];
const newarr2 = arr2.map((data) =>data.length);

console.log(newarr);
console.log(newarr2);

