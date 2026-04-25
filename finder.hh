template <typename T>
class Finder {
    // ...
public:
    Finder() {}

    void add(const T *t);     // Afegeix un
    void update(const T *t);
    void remove(const T *t);

    /**
     * @brief Retorna el conjunt d'objectes amb rectangles total o
     *        parcialment dins de `rect`.
     *
     * Si el nombre de rectangles del contenidor és `n`, el cost
     * de l'algorisme ha de ser O(log n).
     *
     * @param rect El rectangle de cerca
     *
     * @returns Un conjunt de punters a objectes que tenen un rectangle
     *          parcial o totalment dins de `rect`
     */
    std::set<const T *> query(pro2::Rect rect) const;
};
