let text = ReasonReact.stringToElement;

type operation = 
  | Op_None
  | Op_Sum
  | Op_Substract
  | Op_Multiply
  | Op_Devide; /* Should be divide? */
type state = {
  total: float,
  lastCalculation: float,
  input: string,
  operation,
  allClear: bool
};

type action =
  | AllClear
  | Clear
  | UpdatedField(string)
  | Sum
  | Substract
  | Devide
  | Multiply
  | Equals
  | Decimals
  | Negate
  | Percent;

let initialState = {total: 0., lastCalculation: 0., input: "", operation: Op_None, allClear: true};

let parseFloat = (str) =>
  try (float_of_string(str)) {
  | _ => 0.
  };

/* Operation */
let sum = (x, y) => x +. y;

let multiply = (x, y) => x *. y;

let division = (x, y) => x /. y;

let substraction = (x, y) => x -. y;

let negate = (x) => x *. (-1.);

let isInputEmpty = ({input}) => input === "";

let isTotalZero = ({total}) => total === 0.;

let component = ReasonReact.reducerComponent("App");

let make = (_children) => {
  ...component,
  initialState: () => initialState,
  reducer: (action, state) =>
    switch action {
    | AllClear => ReasonReact.Update(initialState)
    | Clear =>
      let total = isInputEmpty(state) ? 0. : state.total;
      ReasonReact.Update({...state, operation: Op_None, input: "", total, allClear: true})
    | UpdatedField(str) => ReasonReact.Update({...state, input: state.input ++ str})
    | Percent =>
      let input = ! isInputEmpty(state) ? state.input |> parseFloat |> string_of_float : "";
      let total = isInputEmpty(state) ? state.total /. 100. : state.total;
      ReasonReact.Update({...state, input, total})
    | Negate =>
      let total = state.input === "" ? (-1.) *. state.total : state.total;
      let input =
        ! isInputEmpty(state) ?
          state.input |> parseFloat |> negate |> string_of_float : state.input;
      ReasonReact.Update({...state, input, total})
    | Decimals =>
      let total = isInputEmpty(state) && isTotalZero(state) ? 0. : state.total;
      let input =
        isInputEmpty(state) && isTotalZero(state) ?
          ".0" : state.input !== "" ? state.input ++ "." : state.input;
      ReasonReact.Update({...state, input, total})
    | Sum =>
      ReasonReact.Update({
        ...state,
        operation: Op_Sum,
        total: state.total +. parseFloat(state.input),
        input: ""
      })
    | Substract =>
      let total =
        if (! isInputEmpty(state) && ! isTotalZero(state)) {
          state.total -. parseFloat(state.input)
        } else if (isInputEmpty(state) && ! isTotalZero(state)) {
          state.total
        } else {
          parseFloat(state.input)
        };
      ReasonReact.Update({...state, operation: Op_Substract, total, input: ""})
    | Multiply =>
      let total =
        if (! isInputEmpty(state)) {
          parseFloat(state.input)
        } else if (! isTotalZero(state) && ! isInputEmpty(state)) {
          state.total *. parseFloat(state.input)
        } else {
          state.lastCalculation
        };
      ReasonReact.Update({...state, operation: Op_Multiply, total, input: ""})
    | Devide =>
      let total =
        if (! isInputEmpty(state)) {
          parseFloat(state.input)
        } else if (! isTotalZero(state) && ! isInputEmpty(state)) {
          state.total /. parseFloat(state.input)
        } else {
          state.lastCalculation
        };
      ReasonReact.Update({...state, operation: Op_Devide, total, input: ""})
    | Equals =>
      switch state.operation {
      | Op_Sum =>
        ReasonReact.Update({
          ...state,
          operation: Op_None,
          total: state.total +. parseFloat(state.input),
          lastCalculation: state.total +. parseFloat(state.input),
          input: ""
        })
      | Op_Substract =>
        ReasonReact.Update({
          ...state,
          total: state.total -. parseFloat(state.input),
          operation: Op_None,
          lastCalculation: state.total -. parseFloat(state.input),
          input: ""
        })
      | Op_Multiply =>
        ReasonReact.Update({
          ...state,
          total: state.total *. parseFloat(state.input),
          lastCalculation: state.total *. parseFloat(state.input),
          input: ""
        })
      | Op_Devide =>
        ReasonReact.Update({
          ...state,
          operation: Op_None,
          total: state.total /. parseFloat(state.input),
          lastCalculation: state.total /. parseFloat(state.input),
          input: ""
        })
      | _ => ReasonReact.NoUpdate
      }
    },
  render: ({send, state}) =>
    <div className="container">
      <div className="calc-body">
        <div className="calc-screen">
          <div className="calc-operation"> (text @@ state.input) </div>
          <div className="calc-typed">
            (text @@ (state.total |> string_of_float))
            <span className="blink-me"> (text @@ "_") </span>
          </div>
        </div>
        <div className="calc-button-row">
          <div className="button c" onClick=((_e) => send(Clear))> ("C" |> text) </div>
          <div className="button c" onClick=((_e) => send(AllClear))> ("CE" |> text) </div>
          <div className="button l" onClick=((_e) => send(Percent))> ("%" |> text) </div>
          <div className="button l" onClick=((_e) => send(Devide))> ("/" |> text) </div>
        </div>
        <div className="calc-button-row">
          <div className="button" onClick=((_e) => send(UpdatedField("7")))> ("7" |> text) </div>
          <div className="button" onClick=((_e) => send(UpdatedField("8")))> ("8" |> text) </div>
          <div className="button" onClick=((_e) => send(UpdatedField("9")))> ("9" |> text) </div>
          <div className="button l" onClick=((_e) => send(Multiply))> ("x" |> text) </div>
        </div>
        <div className="calc-button-row">
          <div className="button" onClick=((_e) => send(UpdatedField("4")))> ("4" |> text) </div>
          <div className="button" onClick=((_e) => send(UpdatedField("5")))> ("5" |> text) </div>
          <div className="button" onClick=((_e) => send(UpdatedField("6")))> ("6" |> text) </div>
          <div className="button l" onClick=((_e) => send(Substract))> ("-" |> text) </div>
        </div>
        <div className="calc-button-row">
          <div className="button" onClick=((_e) => send(UpdatedField("1")))> ("1" |> text) </div>
          <div className="button" onClick=((_e) => send(UpdatedField("2")))> ("2" |> text) </div>
          <div className="button" onClick=((_e) => send(UpdatedField("3")))> ("3" |> text) </div>
          <div className="button l" onClick=((_e) => send(Sum))> ("+" |> text) </div>
        </div>
        <div className="calc-button-row">
          <div className="button" onClick=((_e) => send(Decimals))> ("." |> text) </div>
          <div className="button" onClick=((_e) => send(UpdatedField("0")))> ("0" |> text) </div>
          <div className="button" onClick=((_e) => send(Negate))> ({js|±|js} |> text) </div>
          <div className="button l" onClick=((_e) => send(Equals))> ("=" |> text) </div>
        </div>
      </div>
    </div>
};