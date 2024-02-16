const express = require("express");
const {pool} = require("./db");

const app = express();
const PORT = 8080;
const cors = require("cors");
app.use(cors());

app.use(express.json());

const morgan = require("morgan");
app.use(morgan("dev"));

//app.get("/", (req,res) => {
    //return res.json({
        //name: "chicken",
    //});
//});

app.get("/user/:id", async (req, res) => {
    try {
        if(req.params.id && req.query.name){
            return res.json({
                getId: true,
                id: req.params.id,
                name: req.query.name,
            });
        }
        throw new Error();
    } catch (error) {
      return res.json({
        getID: false,
      });
    }
  });
  
  app.post("/user", async (req, res) => {
    try {

      return res.json({
        signup: true,
        id: req.body.id,
        password: req.body.password,
      });
    } catch (error) {
      return res.json({
        signup: false,
      });
    }
  });
  
  app.patch("/user/:id", async (req, res) => {
    try {
    
      return res.json({
        update: true,
        id: req.params.id,
        name: req.body.name,
      });
    } catch (error) {
      return res.json({
        update: false,
      });
    }
  });
  
  app.delete("/user/:id", async (req, res) => {
      try {
      
        return res.json({
          delete: true,
          id: req.params.id,
        });
      } catch (error) {
        return res.json({
          delete: false,
        });
      }
    });
  app.listen(PORT, () => `this application is running in ${PORT}`);