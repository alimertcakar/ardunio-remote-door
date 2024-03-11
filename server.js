const express = require("express");
const bodyParser = require("body-parser");

const app = express();
const PORT = 80;

let status = "CLOSED";

app.use(bodyParser.json());

app.get("/status", (req, res) => {
  res.send(status);
  status = "CLOSED";
});

app.post("/door", (req, res) => {
  status = "OPEN";
  res.send("OPEN");
});

app.listen(PORT, () => {
  console.log(`Server is running on port ${PORT}`);
});
