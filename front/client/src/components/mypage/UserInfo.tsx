import {useState, useEffect} from 'react';
import axios from 'axios';
import 'styles/mypage/UserInfo.css';
import {userInfo} from 'types/MyPageTypes'

// const dummy = {
//     user :
//     {
//         intraId : "hello",
//         avatar : "https://upload.wikimedia.org/wikipedia/commons/2/2c/Rotating_earth_%28large%29.gif", 
//         nickName : "hello",
//         win : 5,
//         lose : 5,
//         winRate : "50%"
//     }
// }

const id : string = "hello";//임시값

function UserInfo() {
    const [info, setInfo] = useState<userInfo | null>(null);
    useEffect(() => {
        const fetchData = async () => {
            try {
                const getAPI = await axios.get(
                    'http://localhost:3000/users/' + {id} + '/mypage', {
                    headers: {
                        'Content-Type': 'application/json'
                    }
                });
                setInfo(getAPI.data);
            } catch (e) {
                console.log(e);
            }
        };
        fetchData();
    }, []);
    return (
        <div className='user-info'>
            <div id='user-info-left'>
                <img src={info?.user.avatar} id='avatar' alt='프로필사진'></img>
                <button>change</button>
            </div>
            <div id='user-info-right'>
                <div className='user-info-line'>
                    <span className='user-label'>intraID </span>
                    <span>{info?.user.intraId}</span>
                </div>
                <div className='user-info-line'>
                    <span className='user-label'>nickname </span>
                    <input defaultValue={info?.user.nickName}></input>
                    <span> </span>
                    <button>change</button>
                </div>
                <div className='user-info-line'>
                    <span>{info?.user.win} </span>
                    <span>win </span>
                    <span>{info?.user.lose} </span>
                    <span>lose </span>
                    <span>winRate : </span>
                    <span>{info?.user.winRate} </span>
                </div>
            </div>
        </div>
    );
}

export default UserInfo;