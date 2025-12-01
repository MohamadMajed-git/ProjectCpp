import { createBrowserRouter } from "react-router-dom";
import DefaultLayout from "./component/DefaultLayout";
import Home from "./Home";
import Signup from "./Accounts/Signup";
import Branches from "./pages/Branches";
import Login from "./Accounts/Login";
import AHome from "./AdminPages/AHome";
import GuestLayout from "./component/GuestLayout";
import Guest from "./Guest/Guest";
import ADefaultLayout from "./component/ADefaultLayout";

const router = createBrowserRouter([
    
    {
        path: "/",
        element: <GuestLayout />,
        children: [
            {
                path: "/",
                element: <Guest />
            },
        ]
    },
    {
        path: "/",
        element: <DefaultLayout />,
        children: [
            {
                path: "home",
                element: <Home />
            }, {
                path: "branches",
                element: <Branches />
            }
        ]
    },
    {
        path: "/admin",
        element: <ADefaultLayout />,
        children: [
            {
                path: "admin-home",
                element: <AHome />
            }
        ]
    },
    {
        path: "/signup",
        element: <Signup />
    },
    {
        path: "/login",
        element: <Login />
    },
    {
        path: "/branches",
        element: <Branches />
    },
    {
        path: "*",
        element: <div className="flex items-center justify-center h-[90vh]"><h1 className="text-6xl  font-bold text-red-600">Not Found 404</h1></div>
    }


]);

export default router;