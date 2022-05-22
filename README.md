# Race
1.Hướng dẫn cài đặt:
Cài đặt VisualStudio và xem link youtobe:https://www.youtube.com/watch?v=LI-AG1Y_Le8
2.Mô tả chung về trò chơi, các ý tưởng chính:
    +) Người chơi điểu khiển xe vượt qua các chướng ngại vật trên đường
    +) Người chơi sử dụng bốn phím mũi tên để chơi, độ khó tăng dần khi qua từng mốc điểm
    +) Trò chơi có các đối tượng là : người chơi, xe chướng ngại vật, điểm số
3.Mô tả các chức năng đã cài đặt:
    +) Sủ dụng SDL_Image, SDL_TTF, SDL_Mixer
    +) link youtobe: https://youtu.be/RTcdPT1iAh0
4.Các kĩ thuật lập trình được sử dụng: Sử dụng nhiều class chứa từng đối tượng.
    +) Đối tượng tổng,cơ bản, các đối tượng sau đều kế thừa từ đối tượng BaseObject(CarObject, ObstaclesObject, ExplosionObject).
    +) Nhân vật chính : xe đỏ(CarObject).
    +) Chướng ngại vật: xe xanh,vàng(ObstalcesObject).
    +) Đối tượng vụ nổ : ExplosionObject.
    +) Các lớp chức năng như load text lên màn hình (TextObject).
    +) Sử dụng kĩ thuật cho người và chướng ngại vật di chuyển.
    +) Sử dụng các kĩ thuật lập trình từ các lớp trên để thiết kế Menu,HowToPlay,HightScore.
    +) Sử dụng các kĩ thuật hiệu ứng vụ nổ, âm thanh, đếm thời gian.
5.Kết luận, phương án phát triển và điều rút ra khi thực hiện chương trình:
     - Kết luận: Đây là một game cơ bản, nhưng mà cần xử lý rất nhiều các chi tiết nhỏ
     - Phương án phát triển: 
           +) Sẽ tạo ra nhiều chức năng cho người chơi như có thêm mạng sống.
           +) Ăn các item thì được tăng mạng hay tăng tốc trong thời gian ngắn.
           +) Tạo chế độ chơi hai người.
     - Điều rút ra khi thực hiện chương trình:
           +) Cần cải thiện thuật toán nhiều hơn nữa
           +) Cần cải thiện khả năng refactor
           +) Cần học hỏi rất nhiều từ các nguồn khác nhau để cải thiện chương trình
           +) Nâng cao khả năng debug
