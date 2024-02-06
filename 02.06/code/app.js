// 1. 첫번째 방법
// axios
//   .get("https://jsonplaceholder.typicode.com/todos")
//   .then((response) => {
//     // 구현로직
//     console.log(response.data);
//   })
//   .catch((error) => console.error(error));

// 2. 두번째 방법
async function fetchTodos() {
    try {
      const response = await axios.get(
        "https://jsonplaceholder.typicode.com/todos"
      );
      console.log(response.data);
    } catch (error) {
      console.error(error);
    }
  }
  
  fetchTodos();