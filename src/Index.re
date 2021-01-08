switch (ReactDOM.querySelector("#root")) {
| Some(root) => ReactDOM.render(<App name="John" />, root)
| None => ()
};
