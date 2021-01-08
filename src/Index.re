switch (ReactDOM.querySelector("#root")) {
| Some(root) => ReactDOM.render(<Keyboard> <App /> </Keyboard>, root)
| None => ()
};
