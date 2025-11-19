import { createBrowserRouter } from "react-router-dom";
import DefaultLayout from "./component/DefaultLayout";
import Home from "./Home";
import Signup from "./Accounts/Signup";


const router = createBrowserRouter([
    {
        path: "/",
        element:<DefaultLayout/>,
        children: [
            {
                path: "/",
                element: <Home/>
            }
        ]
    },
    {
        path:"/signup",
        element: <Signup/>
    },
    {
        path: "*",
        element: <div className="flex items-center justify-center h-[90vh]"><h1 className="text-6xl  font-bold text-red-600">Not Found 404</h1></div>
    }


]);

export default router;