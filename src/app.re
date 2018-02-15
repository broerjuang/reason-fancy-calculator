let text = ReasonReact.stringToElement;

let component = ReasonReact.statelessComponent("App");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="container">
      <div className="calc-body">
        <div className="calc-screen">
          <div className="calc-operation"> (text @@ "2536 + 419 +") </div>
          <div className="calc-typed">
            (text @@ "2955")
            <span className="blink-me"> (text @@ "_") </span>
          </div>
        </div>
        <div className="calc-button-row">
          <div className="button c"> ("C" |> text) </div>
          <div className="button l"> ("^" |> text) </div>
          <div className="button l"> ("%" |> text) </div>
          <div className="button l"> ("/" |> text) </div>
        </div>
        <div className="calc-button-row">
          <div className="button"> ("7" |> text) </div>
          <div className="button"> ("8" |> text) </div>
          <div className="button"> ("9" |> text) </div>
          <div className="button l"> ("x" |> text) </div>
        </div>
        <div className="calc-button-row">
          <div className="button"> ("4" |> text) </div>
          <div className="button"> ("5" |> text) </div>
          <div className="button"> ("6" |> text) </div>
          <div className="button l"> ("-" |> text) </div>
        </div>
        <div className="calc-button-row">
          <div className="button"> ("1" |> text) </div>
          <div className="button"> ("2" |> text) </div>
          <div className="button"> ("3" |> text) </div>
          <div className="button l"> ("+" |> text) </div>
        </div>
        <div className="calc-button-row">
          <div className="button"> ("." |> text) </div>
          <div className="button"> ("0" |> text) </div>
          <div className="button"> ({js|±|js} |> text) </div>
          <div className="button l"> ("=" |> text) </div>
        </div>
      </div>
    </div>
};