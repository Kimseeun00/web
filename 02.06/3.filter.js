const datas = [3,5,4,2];

const filterDatas = datas.filter(data => {
    if(data>3){
        return data;
    }
});

const bucketlist = [
    {
        id: 1,
        text: "여행 가기",
        done: false,
    },
    {
        id: 2,
        text: "누워 있기",
        done: false,
    },
    {
        id: 3,
        text: "퇴근하기",
        done: false,
    },
    {
        id: 4,
        text: "취업하기",
        done: false,
    }
];
const filterBucket = bucketlist.filter(data => {
    if(data.done === "false"){
        return data;
    }
})

//const todos = bucketlist.filter(li => li.done === false);
console.log(filterBucket);